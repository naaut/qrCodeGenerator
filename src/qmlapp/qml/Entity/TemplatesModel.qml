import QtQuick

QtObject {

    enum Type {
        WiFi,
        Url,
        Email,
        VCard,
        Geo,
        VEvent,
        Crypto,
        Sms,
        SocialMedia,
        SimpleText
    }

    function getModel() {
        return model;
    }

    function getUrl(popupType) {
        switch(popupType) {
            case TemplatesModel.WiFi:
                return Qt.resolvedUrl("../Popups/WifiPopup.qml");
            case TemplatesModel.Url:
                return Qt.resolvedUrl("../Popups/UrlPopup.qml");
            case TemplatesModel.VEvent:
                return Qt.resolvedUrl("../Popups/VEventPopup.qml");
            case TemplatesModel.VCard:
                return Qt.resolvedUrl("../Popups/VCardPopup.qml");
            case TemplatesModel.Crypto:
                return Qt.resolvedUrl("../Popups/CryptoPopup.qml");
            case TemplatesModel.Email:
                return Qt.resolvedUrl("../Popups/EmailPopup.qml");
            case TemplatesModel.Geo:
                return Qt.resolvedUrl("../Popups/GeoPopup.qml");
            case TemplatesModel.Sms:
                return Qt.resolvedUrl("../Popups/SmsPopup.qml");
            case TemplatesModel.SocialMedia:
                return Qt.resolvedUrl("../Popups/SocialMediaPopup.qml");
            case TemplatesModel.SimpleText:
                return Qt.resolvedUrl("../Popups/SimpleTextPopup.qml");
            default:
                console.error("Unexpected popup type " + popupType);
        }
    }

    property var model: [
        { text: qsTr("WiFi"), value: TemplatesModel.WiFi },
        { text: qsTr("Website Link"), value: TemplatesModel.Url },
        { text: qsTr("Social Media Link"), value: TemplatesModel.SocialMedia },
        { text: qsTr("Contact (vCard)"), value: TemplatesModel.VCard },
        { text: qsTr("Calendar (vEvent)"), value: TemplatesModel.VEvent },
        { text: qsTr("Crypto Payment"), value: TemplatesModel.Crypto },
        { text: qsTr("Geolocation"), value: TemplatesModel.Geo },
        { text: qsTr("Email"), value: TemplatesModel.Email },
        { text: qsTr("SMS Message"), value: TemplatesModel.Sms },
        { text: qsTr("Simple Text"), value: TemplatesModel.SimpleText }
   ]
}


