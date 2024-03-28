import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// SMSTO:+1234567890:This is a pre-defined message sent via QR code scan.

PopupTemplate {
    id: root
    objectName: "smsPopup"

    headerText: qsTr("SMS Message")
    resultString: `SMSTO:${phoneNumber.text}:${body.text}`

    TextField {
         id: phoneNumber
         width: parent.width
         placeholderText: qsTr("Phone Number")
         inputMethodHints: Qt.ImhDialableCharactersOnly
     }

    TextArea {
        id: body
        placeholderText: qsTr("SMS text")
        width: parent.width
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }
}

