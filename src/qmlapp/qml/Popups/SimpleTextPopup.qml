import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// SMSTO:+1234567890:This is a pre-defined message sent via QR code scan.

PopupTemplate {
    id: root
    objectName: "simpleTextPopup"

    headerText: qsTr("Any text")
    resultString: `${textArea.text}`

    TextArea {
        id: textArea
        placeholderText: qsTr("Any text")
        width: parent.width
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }
}

