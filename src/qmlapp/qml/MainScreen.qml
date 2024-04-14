import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Window

import injector
import presenters
import core
import entity

import "Entity"

BaseInjectorPage {
    id: root
    objectName: "mainPage"

    signal openSettings
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

        function openSettings() {
            page.injector.openSettings();
        }

        Connections {
            target: page.injector
            function onBackInActive() {
                $presenter.parametrsChanged();
            }
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

                    onTextChanged: {
                        $presenter.incomingString = urlField.text;
                    }

                    Component.onCompleted: {
                        $presenter.incomingString = urlField.text;
                    }

                    MouseArea {
                        id: ma
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        function showTooltip(text) {
                            toolTip.x = ma.mouseX;
                            toolTip.y = ma.mouseY;
                            toolTip.show("Copied to Clipboard!");
                        }

                        onClicked: {
                            $presenter.copyToClipboard(urlField.text);
                            showTooltip("Copied to Clipboard!");
                        }
                    }

                    ToolTip {
                        id: toolTip
                        timeout: 600
                        visible: false
                    }
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

                    Button {
                        width: settingColumn.width
                        text: qsTr("Settings")
                        onClicked: page.openSettings()
                    }

                    Repeater {
                        model: templatesModel.getModel()
                        Button {
                            width: settingColumn.width
                            text: modelData.text
                            onClicked: page.openPopup(modelData.value)
                        }
                    }
                }
            }
        }
    }
}

