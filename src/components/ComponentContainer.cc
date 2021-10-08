#include "components/ComponentContainer.h"



ComponentContainer::ComponentContainer(Battery *battery,
                                       Ble *ble,
                                       BrightnessController *brightness,
                                       DateTime *dateTime,
                                       FirmwareValidator *firmwareValidator,
                                       MotionController *motion,
                                       Settings *settings,
                                       WatchdogView *watchdogView)
{
        _battery = battery;
        _ble = ble;
        _brightness = brightness;
        _dateTime = dateTime;
        _firmwareValidator = firmwareValidator;
        _motion = motion;
        _settings = settings;
        _watchdogView = watchdogView;
}
