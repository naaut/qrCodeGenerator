#include "SettingsPresenter.h"


SettingsPresenter::SettingsPresenter(SettingsUsecaseUnq settings_usecase)
    : QObject()
    , s_settings_usecase(std::move(settings_usecase))
{
    Q_ASSERT(s_settings_usecase);
    loadSettings();
    connect(this, &SettingsPresenter::parametrsChanged, this, &SettingsPresenter::saveSettings);
}

void SettingsPresenter::loadSettings()
{
    const auto settings = s_settings_usecase->loadSettings();
    m_size = settings.size;
    m_border = settings.borderSize;
    m_ecl = settings.errorCorrection;
    m_async = settings.async;
    emit parametrsChanged();
}

void SettingsPresenter::saveSettings()
{
    s_settings_usecase->saveSettings({
        m_size,
        m_border,
        m_ecl,
        m_async
    });
}
