import QtQuick
import entity


QtObject {

    function getModel() {
        return model;
    }

    function getUrl(popupType) {
        switch(popupType) {
            case QrCodeType.WiFi:
                return Qt.resolvedUrl("../Popups/WifiPopup.qml");
            case QrCodeType.Url:
                return Qt.resolvedUrl("../Popups/UrlPopup.qml");
            case QrCodeType.VEvent:
                return Qt.resolvedUrl("../Popups/VEventPopup.qml");
            case QrCodeType.VCard:
                return Qt.resolvedUrl("../Popups/VCardPopup.qml");
            case QrCodeType.Crypto:
                return Qt.resolvedUrl("../Popups/CryptoPopup.qml");
            case QrCodeType.Email:
                return Qt.resolvedUrl("../Popups/EmailPopup.qml");
            case QrCodeType.Geo:
                return Qt.resolvedUrl("../Popups/GeoPopup.qml");
            case QrCodeType.Sms:
                return Qt.resolvedUrl("../Popups/SmsPopup.qml");
            case QrCodeType.SocialMedia:
                return Qt.resolvedUrl("../Popups/SocialMediaPopup.qml");
            case QrCodeType.SimpleText:
                return Qt.resolvedUrl("../Popups/SimpleTextPopup.qml");
            default:
                console.error("Unexpected popup type " + popupType);
        }
    }

    property var model: [
        { text: qsTr("WiFi"), value: QrCodeType.WiFi },
        { text: qsTr("Website Link"), value: QrCodeType.Url },
        { text: qsTr("Social Media Link"), value: QrCodeType.SocialMedia },
        { text: qsTr("Contact (vCard)"), value: QrCodeType.VCard },
        { text: qsTr("Calendar (vEvent)"), value: QrCodeType.VEvent },
        { text: qsTr("Crypto Payment"), value: QrCodeType.Crypto },
        { text: qsTr("Geolocation"), value: QrCodeType.Geo },
        { text: qsTr("Email"), value: QrCodeType.Email },
        { text: qsTr("SMS Message"), value: QrCodeType.Sms },
        { text: qsTr("Simple Text"), value: QrCodeType.SimpleText }
   ]
}
