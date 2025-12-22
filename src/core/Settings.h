#pragma once

#include <QSettings>

class Settings
{
public:
    static QSettings &instance();

private:
    Settings() = default;
};
