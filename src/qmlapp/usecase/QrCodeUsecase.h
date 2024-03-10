#pragma once

#include <QFuture>
#include <QObject>
#include <QString>

#include <memory>

#include <qrcodegen/qrcodegen.hpp>


class QrCodeUsecase : public QObject
{
    Q_OBJECT

public:
    explicit QrCodeUsecase();

    void requestImageAsync(const QString &incomingString,
                            const quint16 size = 1000,
                            const quint16 borderSize = 1,
                            const qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM);

    QString generateTextSvg(const QString &incomingString,
                            const quint16 borderSize = 1,
                            const qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM) const;

    QImage generateImage(const QString &incomingString,
                         const quint16 size = 1000,
                         const quint16 borderSize = 1,
                         const qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM) const;

    QUrl generateUrl(const QString &incomingString,
                     const quint16 size = 1000,
                     const quint16 borderSize = 1,
                     const qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::MEDIUM) const;

signals:
    void imageReady(const QImage & image);

private:
    QString toSvgString(const qrcodegen::QrCode &qr, const quint16 border) const;
    QFuture<void> m_future;
};

using QrCodeUsecaseUnq = std::unique_ptr<QrCodeUsecase>;
