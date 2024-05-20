#pragma once

#include <domain/entity/Entity.h>
#include <qrcodegen/qrcodegen.hpp>

static qrcodegen::QrCode::Ecc toCoreType(const domain::ErrorCorrection::Level &level)
{
    // TODO: can do it better?
    return static_cast<qrcodegen::QrCode::Ecc>(level);
}
