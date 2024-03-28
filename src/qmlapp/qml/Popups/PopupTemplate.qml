import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material


Popup {
    id: root
    objectName: "popupTemplate"

    default property alias content: mainContentColumn.children
    property alias headerText: header.text

    property string resultString: ""
    property var closeCallback

    signal apply(var incomingString)

    focus: true
    implicitWidth: 300
    modal: true

    anchors.centerIn: parent
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    onApply: {
        if (typeof(closeCallback) === "function") {
            closeCallback(resultString);
        }
        root.close();
    }

    Column {
        width: parent.width

        Label {
            id: header
            font.pixelSize: 14
            bottomPadding: 4
        }

        Column {
            id: mainContentColumn
            width: parent.width
            spacing: 4
        }

        Button {
            width: parent.width
            text: qsTr("Apply")

            onClicked: root.apply(resultString);
        }
    }
}

