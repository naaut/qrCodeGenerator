import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import injector
import presenters
import core
import entity

ApplicationWindow {
    width: 640
    height: 540
    visible: true
    title: qsTr("QR Code generator")

    Material.theme: Material.System
    Material.accent: Material.Indigo

    QmlInjector {
        id: root

        anchors.fill: parent

        sourceComponent: FocusScope {
            id: page

            property QrCodePresenter $presenter

            anchors.fill: parent
            focus: true

            Column {
                id: layout

                anchors {
                    top: page.top
                    left: page.left
                    right: page.right
                    topMargin: 2
                    leftMargin: 2
                    rightMargin: 2
                }
                spacing: 4

                TextField {
                    id: url

                    height: 36
                    width: parent.width
                    wrapMode: TextEdit.Wrap
                    focus: true

                    font.pixelSize: 14

                    text: "https://examlple.com"

                    onTextChanged: $presenter.incomingString = url.text;
                    Component.onCompleted: $presenter.incomingString = url.text;
                }

                Row {
                    width: parent.width

                    Item {
                        width: Math.min(layout.width - settingColumn.width - settingColumn.leftPadding - settingColumn.rightPadding,
                                        page.height - url.height)
                        height: width

                        Painter {
                            id: qrCode
                            anchors.fill: parent

                            Connections {
                                target: $presenter
                                function onQrCodeImageChanged() {
                                    qrCode.setImage($presenter.qrCodeImage);
                                }
                            }
                        }
                    }

                    Column {
                        id: settingColumn
                        width: 140
                        leftPadding: 4
                        rightPadding: 4

                        Label {
                            text: qsTr("Border:")
                            font.pixelSize: 14
                        }

                        TextField {
                            id: border

                            height: 30
                            width: parent.width

                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 14

                            text: "1"

                            validator: RegularExpressionValidator {
                                regularExpression: new RegExp("[0-9]+")
                            }

                            onTextChanged: $presenter.border = +border.text;
                        }

                        Label {
                            text: qsTr("Image size:")
                            font.pixelSize: 14
                        }

                        TextField {
                            id: imageSize

                            height: 30
                            width: parent.width

                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 14

                            text: "1000"

                            validator: RegularExpressionValidator {
                                regularExpression: new RegExp("[0-9]+")
                            }

                            onTextChanged: $presenter.size = +text;
                        }

                        Label {
                            text: qsTr("ECL:")
                            font.pixelSize: 14
                        }

                        ComboBox {
                            width: parent.width
                            currentIndex: 1
                            textRole: "text"
                            valueRole: "value"

                            topInset: 0
                            bottomInset: 0

                            model: ListModel {
                                id: cbItems
                                ListElement { text: qsTr("Low"); value: ECL.Low }
                                ListElement { text: qsTr("Medium"); value: ECL.Medium }
                                ListElement { text: qsTr("Quartile"); value: ECL.Quartile }
                                ListElement { text: qsTr("High"); value: ECL.High }
                            }

                            onActivated: $presenter.ecl = currentValue;
                        }

                        Switch {
                            checked: true

                            topPadding: 14
                            leftPadding: 0
                            text: qsTr("Async")

                             onCheckedChanged: $presenter.async = checked;
                        }

                        Button {
                            id: generateButton
                            width: parent.width
                            text: qsTr("Generate")

                            onClicked: $presenter.parametrsChanged(); //TODO: clarify it
                        }
                    }
                }
            }

            Keys.onPressed: (event)=> {
                if (event.key == Qt.Key_Escape) {
                    Qt.quit();
                }
            }
        }
    }
}

