#pragma once

#include <QString>
#include <core/Backend.h>
#include <driver/CanDriver.h>

class AsclCANWinServiceInterface;
class GenericCanSetupPage;

class AsclCANWinServiceDriver: public CanDriver {
public:
    AsclCANWinServiceDriver(Backend &backend);
    virtual ~AsclCANWinServiceDriver();

    virtual QString getName();
    virtual bool update();

private:
    GenericCanSetupPage *setupPage;
};
