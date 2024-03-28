import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// bitcoin:1BoatSLRHtKNngkdXEeobR76b53LETtpyT?amount=0.01

PopupTemplate {
    id: root
    objectName: "cryptoPopup"

    headerText: qsTr("Crypto Payment Address")
    resultString: `${cryptoType.currentValue}:${address.text}?amount=${amount.text}`

    ComboBox {
        id: cryptoType
        width: parent.width

        currentIndex: 0
        textRole: "text"
        valueRole: "value"

        model: ListModel {
            ListElement { text: qsTr("Bitcoin"); value: "bitcoin" }
            ListElement { text: qsTr("Etherium"); value: "ethereum" }
        }
    }

    TextField {
        id: address
        width: parent.width
        placeholderText: qsTr("Crypto Payment Address")
    }

    TextField {
        id: amount
        width: parent.width
        placeholderText: qsTr("Amount")
        validator: DoubleValidator {
            bottom: 0
            notation: DoubleValidator.StandardNotation
        }
    }
}

