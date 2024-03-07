import QtQuick
import QtQuick.Controls

import injector
import presenters

ApplicationWindow {
    width: 640
    height: 680
    visible: true
    title: qsTr("QR Code generator")

    QmlInjector {
        id: root

        anchors.fill: parent

        sourceComponent: FocusScope {
            id: page

            property QrCodePresenter $presenter

            anchors.fill: parent
            focus: true

            TextEdit {
                id: textEdit
                anchors.top: page.top
                padding: 10
                width: parent.width
                wrapMode: TextEdit.Wrap
                focus: true

                font {
                    pixelSize: 14
                }

                text: "https://examlple.com"

                onTextChanged: $presenter.incomingString = text;
            }

            Image {
                id: qrCode

                anchors.top: textEdit.bottom
                width: Math.min(parent.width, parent.height - textEdit.height)
                height: width
                fillMode: Qt.PreserveAspectFit
                source: $presenter.qrCodeUrl
            }

            Keys.onPressed: (event)=> {
                if (event.key == Qt.Key_Escape) {
                    Qt.quit();
                }
            }
        }
    }
}

