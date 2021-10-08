#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H


#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/brightness/BrightnessController.h"
#include "components/datetime/DateTimeController.h"
#include "components/firmwarevalidator/FirmwareValidator.h"
#include "components/motion/MotionController.h"
#include "components/settings/Settings.h"
#include "drivers/Watchdog.h"


using namespace Pinetime::Controllers;
using namespace Pinetime::Drivers;



class ComponentContainer
{
public:

        ComponentContainer();
        ~ComponentContainer();

        Battery *battery() const { return _battery; }
        Ble *ble() const { return _ble; }
        BrightnessController *brightness() const { return _brightness; }
        DateTime *dateTime() const { return _dateTime; }
        FirmwareValidator *firmwareValidator() const { return _firmwareValidator; }
        MotionController *motion() const { return _motion; }
        Settings *settings() const { return _settings; }
        WatchdogView *watchdog() const { return _watchdogView; }

private:

        Battery *_battery;
        Ble *_ble;
        BrightnessController *_brightness;
        DateTime *_dateTime;
        FirmwareValidator *_firmwareValidator;
        MotionController *_motion;
        Settings *_settings;
        Watchdog _watchdog;
        WatchdogView *_watchdogView;
};

#endif // COMPONENTCONTAINER_H
