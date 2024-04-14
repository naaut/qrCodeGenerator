#pragma once

#include <QObject>
#include <QQmlEngine>

#include <core/Entity.h>


class SettingsUsecase : public QObject
{
    Q_OBJECT

public:
    explicit SettingsUsecase();

    void saveSettings(const QrCodeSettings &settings);
    QrCodeSettings loadSettings();
};

using SettingsUsecaseUnq = std::unique_ptr<SettingsUsecase>;
