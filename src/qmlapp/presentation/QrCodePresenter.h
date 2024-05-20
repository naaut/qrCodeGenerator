#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtGui/QImage>

#include <domain/entity/Entity.h>
#include <usecase/GenerationUsecase.h>
#include <usecase/SettingsUsecase.h>


class QrCodePresenter : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QString incomingString MEMBER m_incomingString NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(QImage qrCodeImage READ qrCodeImage NOTIFY qrCodeImageChanged FINAL)

public:
    explicit QrCodePresenter(QrCodeUsecaseUnq generation_usecase, SettingsUsecaseUnq settings_usecase);

    Q_INVOKABLE void copyToClipboard(const QString &text);

    QImage qrCodeImage() const { return m_qrCodeImage; }

signals:
    void parametrsChanged();
    void qrCodeImageChanged();

private:
    void updateQrCode();

private:
    QrCodeUsecaseUnq m_generation_usecase;
    SettingsUsecaseUnq s_settings_usecase;

    QMetaObject::Connection m_requestConnection;

    QString m_incomingString;
    domain::QrCodeSettings m_generation_settings;
    QImage m_qrCodeImage;
};

using QrCodePresenterUnq = std::unique_ptr<QrCodePresenter>;
