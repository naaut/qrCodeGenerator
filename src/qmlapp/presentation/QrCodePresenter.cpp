#include "QrCodePresenter.h"

#include <QByteArray>
#include <QBuffer>
#include <QDebug>


QrCodePresenter::QrCodePresenter(QrCodeUsecaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);

    connect(this, &QrCodePresenter::parametrsChanged, this, &QrCodePresenter::updateQrCode);
}

void QrCodePresenter::updateQrCode()
{
    qDebug() << "Starting update Qr code";
    if (async())
    {
        qDebug() << "async request url";

        m_usecase->requestImageAsync(incomingString(), size(), border(), ErrorCorrection::toCoreType(ecl()));

        connect(m_usecase.get(), &QrCodeUsecase::imageReady, this, [this](QImage image) {
                qDebug() << "async request ready";
                if (image.isNull() || image == m_qrCodeImage) {
                    return;
                }
                this->m_qrCodeImage = image;
                emit qrCodeImageChanged();

            }, Qt::ConnectionType::SingleShotConnection);
    }
    else
    {
        qDebug() << "synchronous request url";
        m_qrCodeImage = m_usecase->generateImage(incomingString(), size(), border(), ErrorCorrection::toCoreType(ecl()));
        emit qrCodeImageChanged();
    }
}

void QrCodePresenter::setIncomingString(const QString & incoming)
{
    if (incoming == m_incomingString)
    {
        return;
    }

    m_incomingString = incoming;
    emit parametrsChanged();
}

void QrCodePresenter::setBorder(const int border)
{

    if (border == m_border)
    {
        return;
    }

    m_border = border;
    emit parametrsChanged();
}

void QrCodePresenter::setSize(const int size)
{
    if (size == m_size)
    {
        return;
    }

    m_size = size;
    emit parametrsChanged();
}

void QrCodePresenter::setEcl(const ErrorCorrection::Level ecl)
{
    if (ecl == m_ecl)
    {
        return;
    }

    m_ecl = ecl;
    emit parametrsChanged();
}

void QrCodePresenter::setAsync(const bool async)
{
    if (async == m_async)
    {
        return;
    }

    m_async = async;
    emit asyncChanged();
}
