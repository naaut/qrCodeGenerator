#pragma once

#include <QObject>
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




