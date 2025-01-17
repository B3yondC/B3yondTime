#include "BrightnessController.h"
#include <hal/nrf_gpio.h>
#include "drivers/PinMap.h"
using namespace Pinetime::Controllers;

void BrightnessController::Init() {
  nrf_gpio_cfg_output(PinMap::LcdBacklightLow);
  nrf_gpio_cfg_output(PinMap::LcdBacklightMedium);
  nrf_gpio_cfg_output(PinMap::LcdBacklightHigh);
  Set(level);
}

void BrightnessController::Set(BrightnessController::Levels level) {
  this->level = level;
  switch (level) {
    default:
    case Levels::High:
      nrf_gpio_pin_clear(PinMap::LcdBacklightLow);
      nrf_gpio_pin_clear(PinMap::LcdBacklightMedium);
      nrf_gpio_pin_clear(PinMap::LcdBacklightHigh);
      break;
    case Levels::Medium:
      nrf_gpio_pin_clear(PinMap::LcdBacklightLow);
      nrf_gpio_pin_clear(PinMap::LcdBacklightMedium);
      nrf_gpio_pin_set(PinMap::LcdBacklightHigh);
      break;
    case Levels::Low:
      nrf_gpio_pin_clear(PinMap::LcdBacklightLow);
      nrf_gpio_pin_set(PinMap::LcdBacklightMedium);
      nrf_gpio_pin_set(PinMap::LcdBacklightHigh);
      break;
    case Levels::Off:
      nrf_gpio_pin_set(PinMap::LcdBacklightLow);
      nrf_gpio_pin_set(PinMap::LcdBacklightMedium);
      nrf_gpio_pin_set(PinMap::LcdBacklightHigh);
      break;
  }
}

void BrightnessController::Lower() {
  switch (level) {
    case Levels::High:
      Set(Levels::Medium);
      break;
    case Levels::Medium:
      Set(Levels::Low);
      break;
    case Levels::Low:
      Set(Levels::Off);
      break;
    default:
      break;
  }
}

void BrightnessController::Higher() {
  switch (level) {
    case Levels::Off:
      Set(Levels::Low);
      break;
    case Levels::Low:
      Set(Levels::Medium);
      break;
    case Levels::Medium:
      Set(Levels::High);
      break;
    default:
      break;
  }
}

BrightnessController::Levels BrightnessController::Level() const {
  return level;
}

void BrightnessController::Backup() {
  backupLevel = level;
}

void BrightnessController::Restore() {
  Set(backupLevel);
}

void BrightnessController::Step() {
  switch (level) {
    case Levels::Low:
      Set(Levels::Medium);
      break;
    case Levels::Medium:
      Set(Levels::High);
      break;
    case Levels::High:
      Set(Levels::Low);
      break;
    default:
      break;
  }
}
