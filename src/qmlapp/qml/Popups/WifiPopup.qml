import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material


PopupTemplate {
    id: root
    objectName: "WifiPopup"

    headerText: qsTr("WiFi")
    resultString: `WIFI:T:${encryptionType.currentValue};S:${ssidInput.text};P:${passwordInput.text};;`

    TextField {
        id: ssidInput
        width: parent.width
        placeholderText: "SSID"
    }

    ComboBox {
        id: encryptionType
        width: parent.width

        currentIndex: 1
        textRole: "text"
        valueRole: "value"

        model: ListModel {
            ListElement { text: qsTr("WEP"); value: "WEP" }
            ListElement { text: qsTr("WPA"); value: "WPA" }
            ListElement { text: qsTr("nopass"); value: "" }
        }
    }

    TextField {
        id: passwordInput
        width: parent.width
        placeholderText: "Password"
        enabled: encryptionType.currentIndex !== 2
    }
}
