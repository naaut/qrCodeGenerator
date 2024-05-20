import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import presenters


Popup {
    id: root
    objectName: "historyPopup"

    property HistoryPresenter historyPresenter
    property var closeCallback

    signal apply(var incomingString)

    anchors.centerIn: parent
    implicitWidth: 400

    focus: true
    modal: true

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    onApply: {
        if (typeof(closeCallback) === "function") {
            closeCallback(incomingString);
        }
        root.close();
    }

    Column {
        width: parent.width

        Label {
            id: header
            text: qsTr("History")
            font.pixelSize: 14
            bottomPadding: 4
        }

        ListView {
            width: parent.width
            height: 500

            clip: true
            model: historyPresenter.historyModel

            footer: Item {
                height: 50
                width: ListView.width

                Button {
                    text: qsTr("Clear History")
                    onClicked: historyPresenter.clearHistory()
                }
            }

            delegate: Item {
                width: ListView.width
                height: 50

                RowLayout {
                    width: ListView.width
                    height: 50
                    spacing: 8

                    Button {
                        id: removeButtton
                        text: qsTr("X")
                        onClicked: historyPresenter.removeHistoryItem(index)
                    }

                    Label {
                        text: model.data.replace(/(\r\n|\n|\r)/gm, " ");
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                root.apply(model.data);
                            }
                        }
                    }
                }
            }

            remove: Transition {
                NumberAnimation {
                    property: "opacity"
                    to: 0.0
                    duration: 500
                }
                NumberAnimation {
                    property: "height"
                    to: 0
                    duration: 500
                }
            }
        }
    }
}

