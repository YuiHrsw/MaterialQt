import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs

import M3Tools 

ApplicationWindow {
    width: 800
    height: 700
    visible: true
    title: "M3 Generator (Native C++)"
    color: generator.background

    // 实例化 C++ 类
    MaterialColorGenerator {
        id: generator
        isDark: switchDark.checked
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 240
            
            color: generator.surface
            
            radius: 16
            clip: true 

            Image {
                id: imgPreview
                anchors.fill: parent
                visible: true 
                fillMode: Image.PreserveAspectCrop
            }
            
            Label {
                anchors.centerIn: parent
                text: "点击选择图片"
                color: generator.onSurface
                visible: imgPreview.status !== Image.Ready
            }

            MouseArea {
                anchors.fill: parent
                onClicked: fileDialog.open()
            }
        }

        RowLayout {
            Label { text: "Dark Mode"; color: generator.onBackground }
            Switch { id: switchDark }
        }

        // 颜色展示：四个色系（Primary / Secondary / Tertiary / Error）
        // 每个色系展示：OnColor, Color, ColorContainer, OnColorContainer
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout {
                anchors.margins: 0
                anchors.fill: parent
                spacing: 12

                component ColorBox: Rectangle {
                    property string title
                    property color c
                    property color txtC
                    Layout.fillWidth: true
                    implicitWidth: 160
                    height: 72
                    color: c
                    radius: 8
                    border.color: Qt.darker(c, 1.02)
                    Text { 
                        text: title; color: txtC; 
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter;
                        font.bold: true
                    }
                }

                // Primary column
                ColumnLayout { Layout.fillWidth: true; spacing: 8
                    ColorBox { title: "On Primary"; c: generator.onPrimary; txtC: generator.primary }
                    ColorBox { title: "Primary"; c: generator.primary; txtC: generator.onPrimary }
                    ColorBox { title: "Primary Container"; c: generator.primaryContainer; txtC: generator.onPrimaryContainer }
                    ColorBox { title: "On Pri Container"; c: generator.onPrimaryContainer; txtC: generator.primaryContainer }
                }

                // Secondary column
                ColumnLayout { Layout.fillWidth: true; spacing: 8
                    ColorBox { title: "On Secondary"; c: generator.onSecondary; txtC: generator.secondary }
                    ColorBox { title: "Secondary"; c: generator.secondary; txtC: generator.onSecondary }
                    ColorBox { title: "Secondary Container"; c: generator.secondaryContainer; txtC: generator.onSecondaryContainer }
                    ColorBox { title: "On Sec Container"; c: generator.onSecondaryContainer; txtC: generator.secondaryContainer }
                }

                // Tertiary column
                ColumnLayout { Layout.fillWidth: true; spacing: 8
                    ColorBox { title: "On Tertiary"; c: generator.onTertiary; txtC: generator.tertiary }
                    ColorBox { title: "Tertiary"; c: generator.tertiary; txtC: generator.onTertiary }
                    ColorBox { title: "Tertiary Container"; c: generator.tertiaryContainer; txtC: generator.onTertiaryContainer }
                    ColorBox { title: "On Ter Container"; c: generator.onTertiaryContainer; txtC: generator.tertiaryContainer }
                }

                ColumnLayout { Layout.fillWidth: true; spacing: 8
                    ColorBox { title: "On Error"; c: generator.onError; txtC: generator.error }
                    ColorBox { title: "Error"; c: generator.error; txtC: generator.onError }
                    ColorBox { title: "Error Container"; c: generator.errorContainer; txtC: generator.onErrorContainer }
                    ColorBox { title: "On Err Container"; c: generator.onErrorContainer; txtC: generator.errorContainer }
                }

                ColumnLayout { Layout.fillWidth: true; spacing: 8
                    ColorBox { title: "Surface Variant"; c: generator.surfaceVariant; txtC: generator.onSurfaceVariant }
                    ColorBox { title: "On Surface Variant"; c: generator.onSurfaceVariant; txtC: generator.surfaceVariant }
                    ColorBox { title: "Inverse Surface"; c: generator.inverseSurface; txtC: generator.inverseOnSurface }
                    ColorBox { title: "Inverse On Surface"; c: generator.inverseOnSurface; txtC: generator.inverseSurface }
                }

                ColumnLayout { Layout.fillWidth: true; spacing: 8
                    ColorBox { title: "Outline"; c: generator.outline; txtC: generator.surface }
                    ColorBox { title: "Outline Variant"; c: generator.outlineVariant; txtC: generator.surface }
                    ColorBox { title: "Surface Tint"; c: generator.surfaceTint; txtC: generator.surface }
                    ColorBox { title: "Inverse Primary"; c: generator.inversePrimary; txtC: generator.primary }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["Images (*.png *.jpg *.jpeg)"]
        onAccepted: {
            imgPreview.source = selectedFile
            generator.generateFromImage(selectedFile)
        }
    }
}