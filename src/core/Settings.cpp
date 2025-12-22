#include "Settings.h"

#include <QStandardPaths>
#include <QDir>

QSettings &Settings::instance()
{
    static QSettings settings([] {
        QString path =
            QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        QDir().mkpath(path);
        return path + "/settings.ini";
    }(), QSettings::IniFormat);

    return settings;
}
