#include "QrCodePresenter.h"

#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>


QrCodePresenter::QrCodePresenter(QrCodeUsecaseUnq generation_usecase, SettingsUsecaseUnq settings_usecase)
    : QObject()
    , m_generation_usecase(std::move(generation_usecase))
    , s_settings_usecase(std::move(settings_usecase))
{
    Q_ASSERT(m_generation_usecase);
    Q_ASSERT(s_settings_usecase);

    m_generation_settings = s_settings_usecase->loadSettings();
    connect(this, &QrCodePresenter::parametrsChanged, this, &QrCodePresenter::updateQrCode);
}

void QrCodePresenter::copyToClipboard(const QString &text)
{
    if (!text.isEmpty())
    {
        QClipboard * clipboard = QGuiApplication::clipboard();
        clipboard->setText(qPrintable(text));
    }
}

void QrCodePresenter::updateQrCode()
{
    m_generation_settings = s_settings_usecase->loadSettings();

    if (m_generation_settings.async)
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

        m_generation_usecase->requestImageAsync(m_incomingString,
                                                m_generation_settings.size,
                                                m_generation_settings.borderSize,
                                                ErrorCorrection::toCoreType(m_generation_settings.errorCorrection));
    }
    else
    {
        qDebug() << "Starting update Qr code with synchronous request url";
        m_qrCodeImage = m_generation_usecase->generateImage(m_incomingString,
                                                            m_generation_settings.size,
                                                            m_generation_settings.borderSize,
                                                            ErrorCorrection::toCoreType(m_generation_settings.errorCorrection));
        emit qrCodeImageChanged();
    }
}
