#pragma once

#include <QtGui/QImage>

#include <memory>


class PrintingUsecase
{
public:
    explicit PrintingUsecase();

    void printQRCode(const QImage &qrImage);
};

using PrintingUsecaseUnq = std::unique_ptr<PrintingUsecase>;
