import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import injector
import presenters
import core
import entity

import "Entity"

QmlInjector {
    id: root

    signal openTemplatesPage()
    signal openPopup(var popupUrl, var properties)

    sourceComponent: Page {
        id: page

        property QmlInjector injector
        property QrCodePresenter $presenter

        anchors.fill: parent
        focus: true

        function popupCallback(incomingString) {
            if (page && urlField) {
                urlField.text = incomingString;
            }
        }

        function openPopup(popupType) {
            page.injector.openPopup(templatesModel.getUrl(popupType), { closeCallback: page.popupCallback });
        }

        TemplatesModel {
            id: templatesModel
        }

        Row {
            id: mainLayout
            width: page.width

            Column {
                id: layout

                spacing: 4
                width: Math.min(mainLayout.width
                                - settingColumn.width
                                - settingColumn.leftPadding
                                - settingColumn.rightPadding,
                                page.height - urlField.height)

                TextField {
                    id: urlField

                    height: 36
                    width: parent.width
                    wrapMode: TextEdit.Wrap
                    focus: true

                    font.pixelSize: 14

                    text: "http://sednev.net/"

                    onTextChanged: $presenter.incomingString = urlField.text;
                    Component.onCompleted: $presenter.incomingString = urlField.text;
                }

                Item {
                    id: imageWrapper
                    width: layout.width
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
            }

            Flickable {
                contentHeight: settingColumn.height
                flickableDirection: Flickable.VerticalFlick
                height: imageWrapper.height
                width: 140

                Column {
                    id: settingColumn
                    width: 180
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
                        inputMask: "9"

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
                        inputMask: "99999"

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

                    Repeater {
                        model: templatesModel.getModel()
                        Button {
                            width: settingColumn.width
                            text: modelData.text
                            onClicked: page.openPopup(modelData.value);
                        }
                    }
                }
            }
        }
    }
}

