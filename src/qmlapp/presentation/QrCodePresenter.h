#pragma once

#include <usecase/QrCodeUsecase.h>
#include <core/Entity.h>

#include <QObject>
#include <QImage>
#include <QString>
#include <QUrl>


class QrCodePresenter : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QString incomingString READ incomingString WRITE setIncomingString NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(int border READ border WRITE setBorder NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(ErrorCorrection::Level ecl READ ecl WRITE setEcl NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(bool async READ async WRITE setAsync NOTIFY asyncChanged FINAL)

    Q_PROPERTY(QUrl qrCodeUrl READ qrCodeUrl  NOTIFY qrCodeUrlChanged FINAL)
    Q_PROPERTY(QImage qrCodeImage READ qrCodeImage  NOTIFY qrCodeImageChanged FINAL)

public:
    explicit QrCodePresenter(QrCodeUsecaseUnq usecase);

    QString incomingString() const { return m_incomingString; }
    int border() const { return m_border; }
    int size() const { return m_size; }
    ErrorCorrection::Level ecl() const { return m_ecl; }
    bool async() const { return m_async; }

    QUrl qrCodeUrl() const { return m_qrCodeUrl; }
    QImage qrCodeImage() const { return m_qrCodeImage; }

signals:
    void parametrsChanged();
    void asyncChanged();
    void qrCodeUrlChanged();
    void qrCodeImageChanged();

private:
    void setIncomingString(const QString & incoming);
    void setBorder(const int border);
    void setSize(const int size);
    void setEcl(const ErrorCorrection::Level ecl);
    void setAsync(const bool async);

    void updateQrCode();

private:
    QrCodeUsecaseUnq m_usecase;

    QString m_incomingString;
    int m_border{1};
    int m_size{1000};
    ErrorCorrection::Level m_ecl{ErrorCorrection::Level::Medium};
    bool m_async{true};

    QUrl m_qrCodeUrl;
    QImage m_qrCodeImage;
};

using QrCodePresenterUnq = std::unique_ptr<QrCodePresenter>;
