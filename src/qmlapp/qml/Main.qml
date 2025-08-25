import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "Popups"

ApplicationWindow {
    width: 840
    height: 700
    visible: true
    title: qsTr("QrCode generator")

    Material.theme: Material.System
    Material.accent: Material.Indigo

    onClosing: {
        mainStack.clear();
    }

    StackView {
        id: mainStack

        anchors.fill: parent

        initialItem: MainScreen {
            onOpenSettings: {
                mainStack.push(Qt.resolvedUrl("SettingsScreen.qml"));
            }

            onOpenPopup: function (popupUrl, properties) {
                popupLoader.open(popupUrl, properties);
            }
        }

        Connections {
            target: mainStack.currentItem
            ignoreUnknownSignals: true

            function onClose() {
                if (mainStack.depth === 1) {
                    Qt.quit();
                } else {
                    mainStack.pop();
                }
            }
        }
    }

    PopupLoader {
        id: popupLoader
        anchors.centerIn: parent
    }
}

