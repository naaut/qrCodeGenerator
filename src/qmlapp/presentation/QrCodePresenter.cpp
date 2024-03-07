#include "QrCodePresenter.h"

#include <QByteArray>
#include <QBuffer>


QrCodePresenter::QrCodePresenter(QrCodeUsecaseUnq usecase)
    : QObject()
    , m_usecase(std::move(usecase))
{
    Q_ASSERT(m_usecase);

    connect(this, &QrCodePresenter::incomingStringChanged, this, &QrCodePresenter::updateQrCode);
}

void QrCodePresenter::updateQrCode()
{
    m_qrCodeUrl = m_usecase->generateUrl(incomingString());

    emit qrCodeUrlChanged();
}

void QrCodePresenter::setIncomingString(const QString & incoming)
{
    if (incoming == m_incomingString)
    {
        return;
    }

    m_incomingString = incoming;
    emit incomingStringChanged();
}
