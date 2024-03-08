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

        m_usecase->requestUrlAsync(incomingString(), size(), border(), ErrorCorrection::toCoreType(ecl()));

        connect(m_usecase.get(), &QrCodeUsecase::imageUrlReady, this, [this](auto url) {
                qDebug() << "async request ready";
                this->m_qrCodeUrl = url;
                emit qrCodeUrlChanged();

            }, Qt::ConnectionType::SingleShotConnection);
    }
    else
    {
        qDebug() << "synchronous request url";

        m_qrCodeUrl = m_usecase->generateUrl(incomingString(), size(), border(), ErrorCorrection::toCoreType(ecl()));
        emit qrCodeUrlChanged();
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
