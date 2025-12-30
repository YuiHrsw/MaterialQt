#include "MaterialColorGenerator.h"

#include <QDebug>
#include <QImage>
#include <vector>

#include "cpp/dynamiccolor/material_dynamic_colors.h"
#include "cpp/quantize/celebi.h"
#include "cpp/scheme/scheme_tonal_spot.h"
#include "cpp/score/score.h"

using namespace material_color_utilities;

static QColor toQColor(Argb argb) {
    return QColor::fromRgba(static_cast<QRgb>(argb));
}

MaterialColorGenerator::MaterialColorGenerator(QObject* parent)
    : QObject(parent) {
    updateTheme();
}

void MaterialColorGenerator::setIsDark(bool dark) {
    if (m_isDark != dark) {
        m_isDark = dark;
        emit isDarkChanged();
        updateTheme();
    }
}

void MaterialColorGenerator::setSeedColor(const QColor& color) {
    if (m_seedColor != color) {
        m_seedColor = color;
        updateTheme();
    }
}

void MaterialColorGenerator::generateFromImage(const QUrl& path) {
    QString localPath = path.toLocalFile();
    if (localPath.isEmpty()) localPath = path.toString();

    QImage image(localPath);
    if (image.isNull()) {
        qWarning() << "Failed to load image:" << localPath;
        return;
    }

    // 缩小图片加速
    QImage small = image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    small = small.convertToFormat(QImage::Format_ARGB32);

    std::vector<Argb> pixels;
    pixels.reserve(small.width() * small.height());

    const int width = small.width();
    const int height = small.height();

    for (int y = 0; y < height; ++y) {
        const QRgb* scanLine = (const QRgb*)small.constScanLine(y);
        for (int x = 0; x < width; ++x) {
            pixels.push_back(static_cast<Argb>(scanLine[x]));
        }
    }

    // 1. 量化 (Quantize)
    // 提取图片中的显著颜色
    QuantizerResult result = QuantizeCelebi(pixels, 128);

    // 2. 评分 (RankedSuggestions)
    // Google 算法会自动过滤掉不适合做主题色的颜色（如太灰、太暗）
    // RankedSuggestions 返回一个排序后的颜色列表，第一个是最佳主色
    std::vector<Argb> ranked = RankedSuggestions(result.color_to_count);

    if (!ranked.empty()) {
        Argb bestColor = ranked[0];
        setSeedColor(toQColor(bestColor));
    }
}

void MaterialColorGenerator::updateTheme() {
    Argb seed = static_cast<Argb>(m_seedColor.rgba());

    // 3. 生成色板 (Scheme)
    SchemeTonalSpot scheme(Hct(seed), m_isDark, 0.0);

    // 4. 获取动态颜色 (Dynamic Colors)
    m_primary = toQColor(MaterialDynamicColors::Primary().GetArgb(scheme));
    m_onPrimary = toQColor(MaterialDynamicColors::OnPrimary().GetArgb(scheme));
    m_primaryContainer = toQColor(MaterialDynamicColors::PrimaryContainer().GetArgb(scheme));
    m_onPrimaryContainer = toQColor(MaterialDynamicColors::OnPrimaryContainer().GetArgb(scheme));

    m_secondary = toQColor(MaterialDynamicColors::Secondary().GetArgb(scheme));
    m_onSecondary = toQColor(MaterialDynamicColors::OnSecondary().GetArgb(scheme));
    m_secondaryContainer = toQColor(MaterialDynamicColors::SecondaryContainer().GetArgb(scheme));
    m_onSecondaryContainer = toQColor(MaterialDynamicColors::OnSecondaryContainer().GetArgb(scheme));

    m_tertiary = toQColor(MaterialDynamicColors::Tertiary().GetArgb(scheme));
    m_onTertiary = toQColor(MaterialDynamicColors::OnTertiary().GetArgb(scheme));
    m_tertiaryContainer = toQColor(MaterialDynamicColors::TertiaryContainer().GetArgb(scheme));
    m_onTertiaryContainer = toQColor(MaterialDynamicColors::OnTertiaryContainer().GetArgb(scheme));

    m_surface = toQColor(MaterialDynamicColors::Surface().GetArgb(scheme));
    m_onSurface = toQColor(MaterialDynamicColors::OnSurface().GetArgb(scheme));
    m_background = toQColor(MaterialDynamicColors::Background().GetArgb(scheme));
    m_onBackground = toQColor(MaterialDynamicColors::OnBackground().GetArgb(scheme));

    // Additional dynamic colors
    m_surfaceVariant = toQColor(MaterialDynamicColors::SurfaceVariant().GetArgb(scheme));
    m_onSurfaceVariant = toQColor(MaterialDynamicColors::OnSurfaceVariant().GetArgb(scheme));
    m_inverseSurface = toQColor(MaterialDynamicColors::InverseSurface().GetArgb(scheme));
    m_inverseOnSurface = toQColor(MaterialDynamicColors::InverseOnSurface().GetArgb(scheme));
    m_outline = toQColor(MaterialDynamicColors::Outline().GetArgb(scheme));
    m_outlineVariant = toQColor(MaterialDynamicColors::OutlineVariant().GetArgb(scheme));
    m_surfaceTint = toQColor(MaterialDynamicColors::SurfaceTint().GetArgb(scheme));
    m_inversePrimary = toQColor(MaterialDynamicColors::InversePrimary().GetArgb(scheme));

    m_error = toQColor(MaterialDynamicColors::Error().GetArgb(scheme));
    m_onError = toQColor(MaterialDynamicColors::OnError().GetArgb(scheme));
    m_errorContainer = toQColor(MaterialDynamicColors::ErrorContainer().GetArgb(scheme));
    m_onErrorContainer = toQColor(MaterialDynamicColors::OnErrorContainer().GetArgb(scheme));

    emit colorsChanged();
}