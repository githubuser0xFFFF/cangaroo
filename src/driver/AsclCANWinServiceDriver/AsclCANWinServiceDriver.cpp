#include "AsclCANWinServiceDriver.h"
#include "AsclCANWinServiceInterface.h"
#include <core/Backend.h>
#include <driver/GenericCanSetupPage.h>


AsclCANWinServiceDriver::AsclCANWinServiceDriver(Backend &backend)
  : CanDriver(backend),
    setupPage(new GenericCanSetupPage())
{
    QObject::connect(&backend, SIGNAL(onSetupDialogCreated(SetupDialog&)), setupPage, SLOT(onSetupDialogCreated(SetupDialog&)));
}

AsclCANWinServiceDriver::~AsclCANWinServiceDriver()
{
}

bool AsclCANWinServiceDriver::update() {

    deleteAllInterfaces();

    auto intf = new AsclCANWinServiceInterface(this);
    addInterface(intf);
    return true;
}

QString AsclCANWinServiceDriver::getName()
{
    return "ATLCAN";
}

