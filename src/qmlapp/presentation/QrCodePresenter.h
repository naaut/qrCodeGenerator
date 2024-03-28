#pragma once

#include <usecase/GenerationUsecase.h>
#include <usecase/PrintingUsecase.h>
#include <core/Entity.h>

#include <QObject>
#include <QImage>
#include <QString>
#include <QUrl>


class QrCodePresenter : public QObject
{
	Q_OBJECT

    Q_PROPERTY(ErrorCorrection::Level ecl MEMBER m_ecl NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(QString incomingString MEMBER m_incomingString NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(bool async MEMBER m_async NOTIFY asyncChanged FINAL)
    Q_PROPERTY(int border MEMBER m_border NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(int size MEMBER m_size NOTIFY parametrsChanged FINAL)

    Q_PROPERTY(QImage qrCodeImage READ qrCodeImage NOTIFY qrCodeImageChanged FINAL)

public:
    explicit QrCodePresenter(QrCodeUsecaseUnq generation_usecase, PrintingUsecaseUnq print_usecase);

    Q_INVOKABLE void print();

    QImage qrCodeImage() const { return m_qrCodeImage; }

signals:
    void asyncChanged();
    void parametrsChanged();
    void qrCodeImageChanged();

private:
    void updateQrCode();

private:
    QrCodeUsecaseUnq m_generation_usecase;
    PrintingUsecaseUnq m_print_usecase;
    QMetaObject::Connection m_requestConnection;

    QString m_incomingString;
    int m_border{1};
    int m_size{1000};
    ErrorCorrection::Level m_ecl{ErrorCorrection::Level::Medium};
    bool m_async{true};

    QImage m_qrCodeImage;
};

using QrCodePresenterUnq = std::unique_ptr<QrCodePresenter>;
