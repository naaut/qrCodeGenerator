import QtQuick

QtObject {
    id: templates

    enum Type {
        WiFi,
        Url,
        Email,
        vCard,
        Geo,
        vEvent,
        Crypto,
        Sms
    }
}
