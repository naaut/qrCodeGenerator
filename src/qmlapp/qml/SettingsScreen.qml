import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import injector
import presenters
import entity


BaseInjectorPage {
    id: root
    objectName: "SettingsScreen"

    sourceComponent: Page {
        id: page

        property QmlInjector injector
        property SettingsPresenter $presenter

        anchors.fill: parent
        focus: true

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

                validator: RegularExpressionValidator {
                    regularExpression: new RegExp("[0-9]+")
                }
                inputMask: "9"

                onTextChanged: {
                    $presenter.border = +border.text;
                }

                Component.onCompleted: {
                    border.text = $presenter.border;
                }
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

                validator: RegularExpressionValidator {
                    regularExpression: new RegExp("[0-9]+")
                }
                inputMask: "99999"

                onTextChanged: {
                    $presenter.size = +text;
                }

                Component.onCompleted: {
                    imageSize.text = $presenter.size;
                }
            }

            Label {
                text: qsTr("ECL:")
                font.pixelSize: 14
            }

            ComboBox {
                width: parent.width

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

                onActivated: {
                    $presenter.ecl = currentValue;
                }

                Component.onCompleted: {
                    currentIndex = $presenter.ecl;
                }
            }

            Switch {
                topPadding: 14
                leftPadding: 0
                text: qsTr("Async")

                onCheckedChanged: {
                    $presenter.async = checked;
                }

                Component.onCompleted: {
                    checked = $presenter.async;
                }
            }

            Button {
                width: parent.width
                text: qsTr("Apply")

                onClicked: page.injector.close();
            }
        }
    }
}

