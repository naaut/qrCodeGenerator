import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// https://www.example.com

PopupTemplate {
    id: root
    objectName: "urlPopup"

    headerText: qsTr("Website URL")
    resultString: `${encryptionType.currentValue}://${urlField.text}`

    ComboBox {
        id: encryptionType
        width: parent.width

        currentIndex: 1

        model: [ "http", "https" ]
    }

    TextField {
        id: urlField
        width: parent.width
        placeholderText: qsTr("Url (without http://)")
    }
}

