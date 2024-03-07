#include "QrCodeUsecase.h"

#include <QBuffer>
#include <QByteArray>
#include <QPainter>
#include <QSvgRenderer>
#include <QTextStream>
#include <QUrl>

QrCodeUsecase::QrCodeUsecase()
{

}

QString QrCodeUsecase::generateTextSvg(const QString &incomingString, const quint16 borderSize, qrcodegen::QrCode::Ecc errorCorrection) const
{
    const auto qrCode = qrcodegen::QrCode::encodeText(incomingString.toUtf8().constData(), errorCorrection);

    return toSvgString(qrCode, borderSize);
}

QImage QrCodeUsecase::generateImage(const QString &incomingString, const quint16 size, const quint16 borderSize, qrcodegen::QrCode::Ecc errorCorrection) const
{
    const auto qrCode = qrcodegen::QrCode::encodeText(incomingString.toUtf8().constData(), errorCorrection);

    QString svg = toSvgString(qrCode, borderSize);
    QSvgRenderer render(svg.toUtf8());
    QImage image(size, size, QImage::Format_Mono);
    image.fill(Qt::white);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    render.render(&painter);
    return image;
}

QUrl QrCodeUsecase::generateUrl(const QString &incomingString, const quint16 size, const quint16 borderSize, qrcodegen::QrCode::Ecc errorCorrection) const
{
    auto image = generateImage(incomingString, size, borderSize, errorCorrection);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "png");
    QString base64 = QString::fromUtf8(byteArray.toBase64());
    return QString("data:image/png;base64,") + base64;
}


QString QrCodeUsecase::toSvgString(const qrcodegen::QrCode &qr, quint16 border) const
{
    QString str;
    QTextStream sb(&str);

    sb << R"(<?xml version="1.0" encoding="UTF-8"?>)"
       << R"(<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">)"
       << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1" viewBox="0 0 )"
       << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2)
       << R"(" stroke="none"><rect width="100%" height="100%" fill="#FFFFFF"/><path d=")";

    for (int y = 0; y < qr.getSize(); y++)
    {
        for (int x = 0; x < qr.getSize(); x++)
        {
            if (qr.getModule(x, y))
            {
                sb << (x == 0 && y == 0 ? "" : " ") << "M" << (x + border) << "," << (y + border)
                   << "h1v1h-1z";
            }
        }
    }

    sb << R"(" fill="#000000"/></svg>)";
    return str;
}
