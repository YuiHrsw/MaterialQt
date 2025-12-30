#pragma once

#include <QColor>
#include <QImage>
#include <QObject>
#include <QQmlEngine>
#include <QUrl>

class MaterialColorGenerator : public QObject {
    Q_OBJECT
    QML_ELEMENT  // 允许在 QML 中直接实例化

    // 定义 Material 3 核心色板属性
    Q_PROPERTY(QColor seedColor READ seedColor NOTIFY colorsChanged)

    Q_PROPERTY(QColor primary READ primary NOTIFY colorsChanged)
    Q_PROPERTY(QColor onPrimary READ onPrimary NOTIFY colorsChanged)
    Q_PROPERTY(QColor primaryContainer READ primaryContainer NOTIFY colorsChanged)
    Q_PROPERTY(QColor onPrimaryContainer READ onPrimaryContainer NOTIFY colorsChanged)

    Q_PROPERTY(QColor secondary READ secondary NOTIFY colorsChanged)
    Q_PROPERTY(QColor onSecondary READ onSecondary NOTIFY colorsChanged)
    Q_PROPERTY(QColor secondaryContainer READ secondaryContainer NOTIFY colorsChanged)
    Q_PROPERTY(QColor onSecondaryContainer READ onSecondaryContainer NOTIFY colorsChanged)

    Q_PROPERTY(QColor tertiary READ tertiary NOTIFY colorsChanged)
    Q_PROPERTY(QColor onTertiary READ onTertiary NOTIFY colorsChanged)
    Q_PROPERTY(QColor tertiaryContainer READ tertiaryContainer NOTIFY colorsChanged)
    Q_PROPERTY(QColor onTertiaryContainer READ onTertiaryContainer NOTIFY colorsChanged)

    Q_PROPERTY(QColor surface READ surface NOTIFY colorsChanged)
    Q_PROPERTY(QColor onSurface READ onSurface NOTIFY colorsChanged)
    Q_PROPERTY(QColor background READ background NOTIFY colorsChanged)
    Q_PROPERTY(QColor onBackground READ onBackground NOTIFY colorsChanged)

    // Additional Material color properties
    Q_PROPERTY(QColor surfaceVariant READ surfaceVariant NOTIFY colorsChanged)
    Q_PROPERTY(QColor onSurfaceVariant READ onSurfaceVariant NOTIFY colorsChanged)
    Q_PROPERTY(QColor inverseSurface READ inverseSurface NOTIFY colorsChanged)
    Q_PROPERTY(QColor inverseOnSurface READ inverseOnSurface NOTIFY colorsChanged)
    Q_PROPERTY(QColor outline READ outline NOTIFY colorsChanged)
    Q_PROPERTY(QColor outlineVariant READ outlineVariant NOTIFY colorsChanged)
    Q_PROPERTY(QColor surfaceTint READ surfaceTint NOTIFY colorsChanged)
    Q_PROPERTY(QColor inversePrimary READ inversePrimary NOTIFY colorsChanged)

    Q_PROPERTY(QColor error READ error NOTIFY colorsChanged)
    Q_PROPERTY(QColor onError READ onError NOTIFY colorsChanged)
    Q_PROPERTY(QColor errorContainer READ errorContainer NOTIFY colorsChanged)
    Q_PROPERTY(QColor onErrorContainer READ onErrorContainer NOTIFY colorsChanged)

    Q_PROPERTY(bool isDark READ isDark WRITE setIsDark NOTIFY isDarkChanged)

    public : explicit MaterialColorGenerator(QObject* parent = nullptr);

    // 从图片路径提取主色并生成色板
    Q_INVOKABLE void generateFromImage(const QUrl& path);

    // 直接设置种子颜色
    Q_INVOKABLE void setSeedColor(const QColor& color);

    // Getters
    QColor seedColor() const { return m_seedColor; }
    bool isDark() const { return m_isDark; }
    void setIsDark(bool dark);

    // 巨大的 Getter 列表 (实现略，见 cpp)
    QColor primary() const { return m_primary; }
    QColor onPrimary() const { return m_onPrimary; }
    QColor primaryContainer() const { return m_primaryContainer; }
    QColor onPrimaryContainer() const { return m_onPrimaryContainer; }

    QColor secondary() const { return m_secondary; }
    QColor onSecondary() const { return m_onSecondary; }
    QColor secondaryContainer() const { return m_secondaryContainer; }
    QColor onSecondaryContainer() const { return m_onSecondaryContainer; }

    QColor tertiary() const { return m_tertiary; }
    QColor onTertiary() const { return m_onTertiary; }
    QColor tertiaryContainer() const { return m_tertiaryContainer; }
    QColor onTertiaryContainer() const { return m_onTertiaryContainer; }

    QColor surface() const { return m_surface; }
    QColor onSurface() const { return m_onSurface; }
    QColor background() const { return m_background; }
    QColor onBackground() const { return m_onBackground; }

    QColor surfaceVariant() const { return m_surfaceVariant; }
    QColor onSurfaceVariant() const { return m_onSurfaceVariant; }
    QColor inverseSurface() const { return m_inverseSurface; }
    QColor inverseOnSurface() const { return m_inverseOnSurface; }
    QColor outline() const { return m_outline; }
    QColor outlineVariant() const { return m_outlineVariant; }
    QColor surfaceTint() const { return m_surfaceTint; }
    QColor inversePrimary() const { return m_inversePrimary; }

    QColor error() const { return m_error; }
    QColor onError() const { return m_onError; }
    QColor errorContainer() const { return m_errorContainer; }
    QColor onErrorContainer() const { return m_onErrorContainer; }

    // int colorCount() const { return m_colorCount; }

   signals:
    void colorsChanged();
    void isDarkChanged();

   private:
    void updateTheme();

    QColor m_seedColor = QColor("#6750A4");  // 默认紫色
    bool m_isDark = false;

    // 缓存生成的颜色
    QColor m_primary, m_onPrimary, m_primaryContainer, m_onPrimaryContainer;
    QColor m_secondary, m_onSecondary, m_secondaryContainer, m_onSecondaryContainer;
    QColor m_tertiary, m_onTertiary, m_tertiaryContainer, m_onTertiaryContainer;
    QColor m_surface, m_onSurface, m_background, m_onBackground;

    QColor m_surfaceVariant, m_onSurfaceVariant, m_inverseSurface, m_inverseOnSurface;
    QColor m_outline, m_outlineVariant, m_surfaceTint, m_inversePrimary;

    QColor m_error, m_onError, m_errorContainer, m_onErrorContainer;
};