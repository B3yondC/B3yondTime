#include "components/ComponentContainer.h"


using namespace Pinetime::Controllers;
using namespace Pinetime::Drivers;



ComponentContainer::ComponentContainer()
{
        _battery = new Battery();
        _ble = new Ble();
        _brightness = new BrightnessController();
        _dateTime = new DateTime();
        _firmwareValidator = new FirmwareValidator();
        _motion = new MotionController();
        _settings = new Settings();
        _watchdogView = new WatchdogView(_watchdog);
}


ComponentContainer::~ComponentContainer()
{
        delete _battery;
        delete _ble;
        delete _brightness;
        delete _dateTime;
        delete _firmwareValidator;
        delete _motion;
        delete _settings;
        delete _watchdogView;
}
