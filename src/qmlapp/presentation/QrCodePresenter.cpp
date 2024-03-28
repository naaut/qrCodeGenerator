#include "QrCodePresenter.h"

#include <QByteArray>
#include <QBuffer>
#include <QDebug>


QrCodePresenter::QrCodePresenter(QrCodeUsecaseUnq generation_usecase, PrintingUsecaseUnq print_usecase)
    : QObject()
    , m_generation_usecase(std::move(generation_usecase))
    , m_print_usecase(std::move(print_usecase))
{
    Q_ASSERT(m_generation_usecase);
    Q_ASSERT(m_print_usecase);

    connect(this, &QrCodePresenter::parametrsChanged, this, &QrCodePresenter::updateQrCode);
}

void QrCodePresenter::print()
{
    m_print_usecase->printQRCode(m_qrCodeImage);
}

void QrCodePresenter::updateQrCode()
{
    if (m_async)
    {
        qDebug() << "Starting update Qr code with async request url";

        if (m_requestConnection)
        {
            QObject::disconnect(m_requestConnection);
        }

        m_requestConnection = connect(m_generation_usecase.get(), &QrCodeUsecase::imageReady, this, [this](QImage image) {
                qDebug() << "async request ready";
                if (image.isNull() || image == m_qrCodeImage)
                {
                    return;
                }
                this->m_qrCodeImage = image;
                emit qrCodeImageChanged();
            }, Qt::ConnectionType::SingleShotConnection);

        m_generation_usecase->requestImageAsync(m_incomingString, m_size, m_border, ErrorCorrection::toCoreType(m_ecl));
    }
    else
    {
        qDebug() << "Starting update Qr code with synchronous request url";
        m_qrCodeImage = m_generation_usecase->generateImage(m_incomingString, m_size, m_border, ErrorCorrection::toCoreType(m_ecl));
        emit qrCodeImageChanged();
    }
}
