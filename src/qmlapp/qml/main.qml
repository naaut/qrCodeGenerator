import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import injector
import presenters
import Entity

ApplicationWindow {
    width: 640
    height: 680
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
                bottomPadding: 4
                spacing: 1

                TextField {
                    id: url


                    height: 30
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

                    Image {
                        id: qrCode
                        width: Math.min(layout.width - settingColumn.width - settingColumn.leftPadding - settingColumn.rightPadding,
                                        page.height - url.height)
                        fillMode: Image.PreserveAspectFit
                        source: $presenter.qrCodeUrl
                    }

                    Column {
                        id: settingColumn
                        width: 140
                        leftPadding: 4
                        rightPadding: 4

                        Label {
                            text: "Border:"
                            font.pixelSize: 14
                        }

                        TextField {
                            id: border

                            height: 30
                            width: parent.width

                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 14

                            text: "1"

                            onTextChanged: $presenter.border = +border.text;
                        }

                        Label {
                            text: "Image size:"
                            font.pixelSize: 14
                        }

                        TextField {
                            id: imageSize

                            height: 30
                            width: parent.width

                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 14

                            text: "1000"

                            onTextChanged: $presenter.size = +text;
                        }

                        Label {
                            text: "ECL:"
                            font.pixelSize: 14
                        }

                        SpinBox {
                            id: spinBox

                            height: 30
                            width: parent.width

                            from: 0
                            to: items.length - 1
                            value: 1 // "Medium"

                            readonly property var items: ["Low", "Medium", "Quartile", "High"]
                            readonly property var valueToEnum: [
                                ECL.Low,
                                ECL.Medium,
                                ECL.Quartile,
                                ECL.High,
                            ]

                            validator: RegularExpressionValidator {
                                regularExpression: new RegExp("(Low|Medium|Quartile|High)", "i")
                            }

                            textFromValue: function(value) {
                                return items[value];
                            }

                            onValueChanged: $presenter.ecl = valueToEnum[value];
                        }

                        Switch {
                            checked: true
                            onCheckedChanged: $presenter.async = checked;
                            topPadding: 14
                            leftPadding: 0
                            text: "Async"
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

