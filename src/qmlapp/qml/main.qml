import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "Popups"

ApplicationWindow {
    width: 840
    height: 700
    visible: true
    title: qsTr("QR Code generator")

    Material.theme: Material.System
    Material.accent: Material.Indigo

    StackView {
        id: mainStack

        anchors.fill: parent

        initialItem: MainScreen {
            // onOpenTemplatesPage: {
            //     mainStack.push(Qt.resolvedUrl("TemplatesScreen.qml"));
            // }

            onOpenPopup: function (popupUrl, properties) {
                popupLoader.open(popupUrl, properties);
            }
        }

        Connections {
            target: mainStack.currentItem
            ignoreUnknownSignals: true

            function onClose() {
                mainStack.pop();
            }
        }

        Keys.onPressed: (event)=> {
            if (event.key == Qt.Key_Escape) {
                Qt.quit();
            }
        }
    }

    PopupLoader {
        id: popupLoader
        anchors.centerIn: parent
    }
}

