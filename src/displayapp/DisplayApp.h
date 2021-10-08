#pragma once
#include <FreeRTOS.h>
#include <date/date.h>
#include <queue.h>
#include <task.h>
#include <memory>
#include <systemtask/Messages.h>
#include "LittleVgl.h"
#include "TouchEvents.h"
#include "components/brightness/BrightnessController.h"
#include "components/motor/MotorController.h"
#include "components/firmwarevalidator/FirmwareValidator.h"
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"
#include "components/timer/TimerController.h"
#include "components/alarm/AlarmController.h"
#include "touchhandler/TouchHandler.h"

#include "SystemInterface.h"

#include "Messages.h"

class ComponentContainer;
class ScreenGraph;


namespace Pinetime {

  namespace Drivers {
    class St7789;
    class Cst816S;
    class WatchdogView;
  }
  namespace Controllers {
    class Settings;
    class Battery;
    class Ble;
    class BrightnessController;
    class DateTime;
    class NotificationManager;
    class HeartRateController;
    class MotionController;
    class TouchHandler;
  }

  namespace System {
    class SystemTask;
  };
  namespace Applications {
    class DisplayApp : public SystemInterface {
    public:
      enum class States { Idle, Running };

      DisplayApp(Drivers::St7789& lcd,
                 Components::LittleVgl& lvgl,
                 Drivers::Cst816S&,
                 Controllers::Battery& batteryController,
                 Controllers::Ble& bleController,
                 Controllers::DateTime& dateTimeController,
                 Drivers::WatchdogView& watchdog,
                 Controllers::NotificationManager& notificationManager,
                 Controllers::HeartRateController& heartRateController,
                 Controllers::Settings& settingsController,
                 Controllers::MotorController& motorController,
                 Controllers::MotionController& motionController,
                 Controllers::TimerController& timerController,
                 Controllers::AlarmController& alarmController,
                 Controllers::TouchHandler& touchHandler);
      ~DisplayApp() override;

      void Start();
      void PushMessage(Display::Messages msg);

      void setFullRefreshDirection(SystemInterface::FullRefreshDirection value) override;

      void Register(Pinetime::System::SystemTask* systemTask);

    private:
      Pinetime::Drivers::St7789& lcd;
      Pinetime::Components::LittleVgl& lvgl;
      Pinetime::Drivers::Cst816S& touchPanel;
      Pinetime::Controllers::Battery& batteryController;
      Pinetime::Controllers::Ble& bleController;
      Pinetime::Controllers::DateTime& dateTimeController;
      Pinetime::Drivers::WatchdogView& watchdog;
      Pinetime::System::SystemTask* systemTask = nullptr;
      Pinetime::Controllers::NotificationManager& notificationManager;
      Pinetime::Controllers::HeartRateController& heartRateController;
      Pinetime::Controllers::Settings& settingsController;
      Pinetime::Controllers::MotorController& motorController;
      Pinetime::Controllers::MotionController& motionController;
      Pinetime::Controllers::TimerController& timerController;
      Pinetime::Controllers::AlarmController& alarmController;
      Pinetime::Controllers::TouchHandler& touchHandler;

      Pinetime::Controllers::FirmwareValidator validator;
      Controllers::BrightnessController brightnessController;

      TaskHandle_t taskHandle;

      States state = States::Running;
      QueueHandle_t msgQueue;

      static constexpr uint8_t queueSize = 10;
      static constexpr uint8_t itemSize = 1;

      ComponentContainer *_components;
      ScreenGraph *_screenGraph;

      TouchEvents returnTouchEvent = TouchEvents::None;

      void RunningState();
      void IdleState();
      static void Process(void* instance);
      void InitHw();
      void Refresh();
      void PushMessageToSystemTask(Pinetime::System::Messages message);

      TickType_t lastWakeTime;
    };
  }
}
