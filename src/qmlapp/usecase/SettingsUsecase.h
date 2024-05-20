#pragma once

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include <domain/entity/Entity.h>


class SettingsUsecase : public QObject
{
    Q_OBJECT

public:
    explicit SettingsUsecase();

    void saveSettings(const domain::QrCodeSettings &settings);
    domain::QrCodeSettings loadSettings();
};

using SettingsUsecaseUnq = std::unique_ptr<SettingsUsecase>;
