#pragma once

#include <QtCore/QObject>

#include <memory>

#include <usecase/SettingsUsecase.h>


class SettingsPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(domain::ErrorCorrection::Level ecl MEMBER m_ecl NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(bool async MEMBER m_async NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(int border MEMBER m_border NOTIFY parametrsChanged FINAL)
    Q_PROPERTY(int size MEMBER m_size NOTIFY parametrsChanged FINAL)

public:
    explicit SettingsPresenter(SettingsUsecaseUnq settings_usecase);

signals:
    void parametrsChanged();
    void qrCodeImageChanged();

private:
   void loadSettings();
   void saveSettings();

private:
    SettingsUsecaseUnq s_settings_usecase;

    int m_size{1000};
    int m_border{1};
    domain::ErrorCorrection::Level m_ecl{domain:: ErrorCorrection::Level::Medium};
    bool m_async{true};
};

using SettingsPresenterUnq = std::unique_ptr<SettingsPresenter>;
