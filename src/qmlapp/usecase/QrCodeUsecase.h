#pragma once

#include <QObject>
#include <QString>

#include <memory>

#include <qrcodegen/qrcodegen.hpp>


class QrCodeUsecase : public QObject
{
    Q_OBJECT

public:
    explicit QrCodeUsecase();

    QString generateTextSvg(const QString &incomingString, const quint16 borderSize = 1,
                          qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM) const;

    QImage generateImage(const QString &incomingString, const quint16 size = 1000, const quint16 borderSize = 1,
                      qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM) const;

    QUrl generateUrl(const QString &incomingString, const quint16 size = 1000, const quint16 borderSize = 1,
                     qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM) const;

private:
    QString toSvgString(const qrcodegen::QrCode &qr, quint16 border) const;
};

using QrCodeUsecaseUnq = std::unique_ptr<QrCodeUsecase>;
