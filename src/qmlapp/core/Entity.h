#pragma once

#include <QObject>
#include <QMetaType>
#include <qrcodegen/qrcodegen.hpp>


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

    static qrcodegen::QrCode::Ecc toCoreType(const ErrorCorrection::Level & level)
    {
        // TODO: can do it better?
        return static_cast<qrcodegen::QrCode::Ecc>(level);
    }
};


struct QrCodeSettings {
    int size{1000};
    int borderSize{1};
    ErrorCorrection::Level errorCorrection{ErrorCorrection::Level::Medium};
    bool async{true};
};
