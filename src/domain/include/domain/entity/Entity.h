#pragma once

#include <QtCore/QObject>
#include <QtCore/QMetaType>

namespace domain
{

class ErrorCorrection  {

    Q_GADGET

public:

    enum Level
    {
        Low = 0,    // tolerate about  7%
        Medium,     // tolerate about 15%
        Quartile,   // tolerate about 25%
        High,       // tolerate about 30%
    };
    Q_ENUM(Level)
};


class QrCode {

    Q_GADGET

public:

    enum Type {
        WiFi = 0,
        Url,
        Email,
        VCard,
        Geo,
        VEvent,
        Crypto,
        Sms,
        SocialMedia,
        SimpleText
    };
    Q_ENUM(Type)
};


struct QrCodeSettings {
    int size{1000};
    int borderSize{1};
    ErrorCorrection::Level errorCorrection{ErrorCorrection::Level::Medium};
    bool async{true};
};

} // namespace domain
