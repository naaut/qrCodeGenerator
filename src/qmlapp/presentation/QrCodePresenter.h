#pragma once

#include <usecase/QrCodeUsecase.h>

#include <QObject>
#include <QString>
#include <QUrl>


class QrCodePresenter : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QString incomingString READ incomingString WRITE setIncomingString NOTIFY incomingStringChanged FINAL)
    Q_PROPERTY(QUrl qrCodeUrl READ qrCodeUrl  NOTIFY qrCodeUrlChanged FINAL)

public:
    explicit QrCodePresenter(QrCodeUsecaseUnq usecase);

    QString incomingString() const { return m_incomingString; }
    QUrl qrCodeUrl() const { return m_qrCodeUrl; }

signals:
    QString incomingStringChanged();
    QUrl qrCodeUrlChanged();

private:
    void setIncomingString(const QString & incoming);
    void updateQrCode();

private:
    QrCodeUsecaseUnq m_usecase;

    QString m_incomingString;
    QUrl m_qrCodeUrl;

};

using QrCodePresenterUnq = std::unique_ptr<QrCodePresenter>;
