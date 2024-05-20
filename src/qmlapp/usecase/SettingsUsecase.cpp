#include "SettingsUsecase.h"

#include <QtCore/QSettings>


SettingsUsecase::SettingsUsecase() {

}

void SettingsUsecase::saveSettings(const domain::QrCodeSettings &settings)
{
    QSettings qsettings("QrCode Generator", "sednev.net");
    qsettings.setValue(QLatin1String("qrSize"), settings.size);
    qsettings.setValue(QLatin1String("qrBorderSize"), settings.borderSize);
    qsettings.setValue(QLatin1String("qrErrorCorrection"), settings.errorCorrection);
    qsettings.setValue(QLatin1String("async"), settings.async);
}

domain::QrCodeSettings SettingsUsecase::loadSettings()
{
    QSettings qsettings("QrCode Generator", "sednev.net");
    domain::QrCodeSettings settings;
    settings.size = qsettings.value(QLatin1String("qrSize"), 1000).toInt();
    settings.borderSize = qsettings.value(QLatin1String("qrBorderSize"), 1).toInt();
    settings.errorCorrection = qsettings.value(QLatin1String("qrErrorCorrection"), domain::ErrorCorrection::Level::Medium)
                                   .value<domain::ErrorCorrection::Level>();
    settings.async = qsettings.value(QLatin1String("async"), true).toBool();
    return settings;
}
