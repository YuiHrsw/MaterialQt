import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Effects

import M3Tools 

ApplicationWindow {
    width: 400
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
            Layout.preferredHeight: 200
            
            color: generator.surfaceVariant 
            
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
                color: generator.onSurfaceVariant
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

        // 颜色展示网格
        GridLayout {
            columns: 2
            Layout.fillWidth: true
            
            component ColorBox: Rectangle {
                property string title
                property color c
                property color txtC
                Layout.fillWidth: true
                height: 60
                color: c
                radius: 8
                Text { 
                    text: title; color: txtC; 
                    anchors.centerIn: parent; font.bold: true 
                }
            }

            ColorBox { title: "Primary"; c: generator.primary; txtC: generator.onPrimary }
            ColorBox { title: "Pri-Container"; c: generator.primaryContainer; txtC: generator.onPrimaryContainer }
            
            ColorBox { title: "Secondary"; c: generator.secondary; txtC: generator.onSecondary }
            ColorBox { title: "Sec-Container"; c: generator.secondaryContainer; txtC: generator.onSecondaryContainer }

            ColorBox { title: "Tertiary"; c: generator.tertiary; txtC: generator.onTertiary }
            ColorBox { title: "Ter-Container"; c: generator.tertiaryContainer; txtC: generator.onTertiaryContainer }
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