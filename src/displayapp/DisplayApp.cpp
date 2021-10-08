#include "DisplayApp.h"

#include <libraries/log/nrf_log.h>
#include "components/ble/NotificationManager.h"
#include "components/motor/MotorController.h"
#include "components/ComponentContainer.h"

#include "displayapp/screens/DefaultScreenGraph.h"

#include "drivers/Cst816s.h"
#include "drivers/St7789.h"
#include "drivers/Watchdog.h"
#include "systemtask/SystemTask.h"
#include "systemtask/Messages.h"

#include "libs/lv_conf.h"


#define INITIAL_SCREEN   ScreenGraph::ScreenTag::AnalogWatchFace


using namespace Pinetime::Applications;
using namespace Pinetime::Applications::Display;



namespace
{
        static inline bool in_isr(void) { return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0; }

        TouchEvents ConvertGesture(Pinetime::Drivers::Cst816S::Gestures gesture)
        {
                switch (gesture) {
                case Pinetime::Drivers::Cst816S::Gestures::SingleTap:
                        return TouchEvents::Tap;
                case Pinetime::Drivers::Cst816S::Gestures::LongPress:
                        return TouchEvents::LongTap;
                case Pinetime::Drivers::Cst816S::Gestures::DoubleTap:
                        return TouchEvents::DoubleTap;
                case Pinetime::Drivers::Cst816S::Gestures::SlideRight:
                        return TouchEvents::SwipeRight;
                case Pinetime::Drivers::Cst816S::Gestures::SlideLeft:
                        return TouchEvents::SwipeLeft;
                case Pinetime::Drivers::Cst816S::Gestures::SlideDown:
                        return TouchEvents::SwipeDown;
                case Pinetime::Drivers::Cst816S::Gestures::SlideUp:
                        return TouchEvents::SwipeUp;
                case Pinetime::Drivers::Cst816S::Gestures::None:
                default:
                        return TouchEvents::None;
                }
        }
}



DisplayApp::DisplayApp(Drivers::St7789& lcd,
                       Components::LittleVgl& lvgl,
                       Drivers::Cst816S& touchPanel,
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
                       Controllers::TouchHandler& touchHandler)
        : lcd {lcd},
          lvgl {lvgl},
          touchPanel {touchPanel},
          batteryController {batteryController},
          bleController {bleController},
          dateTimeController {dateTimeController},
          watchdog {watchdog},
          notificationManager {notificationManager},
          heartRateController {heartRateController},
          settingsController {settingsController},
          motorController {motorController},
          motionController {motionController},
          timerController {timerController},
          alarmController {alarmController},
          touchHandler {touchHandler}
{
        _components = new ComponentContainer(&batteryController,
                                             &bleController,
                                             &brightnessController,
                                             &dateTimeController,
                                             &validator,
                                             &motionController,
                                             &settingsController,
                                             &watchdog);
        _screenGraph = nullptr;
}


DisplayApp::~DisplayApp()
{
        if (_screenGraph)
                delete _screenGraph;
        delete _components;
}


void DisplayApp::Start()
{
        msgQueue = xQueueCreate(queueSize, itemSize);

        // start default screen graph when smartwatch boots
        if (!_screenGraph)
                _screenGraph = new DefaultScreenGraph(this, _components);
        _screenGraph->activateScreen(INITIAL_SCREEN);

        if (pdPASS != xTaskCreate(DisplayApp::Process, "displayapp", 800, this, 0, &taskHandle))
                APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
}


void DisplayApp::Process(void* instance)
{
        auto* app = static_cast<DisplayApp*>(instance);
        NRF_LOG_INFO("displayapp task started!");
        app->InitHw();

        // Send a dummy notification to unlock the lvgl display driver for the first iteration
        xTaskNotifyGive(xTaskGetCurrentTaskHandle());

        while (true)
                app->Refresh();
}


void DisplayApp::InitHw()
{
        brightnessController.Init();
        brightnessController.Set(settingsController.GetBrightness());
}


void DisplayApp::Refresh()
{
        TickType_t queueTimeout;
        TickType_t delta;
        switch (state)
        {
        case States::Idle:
                IdleState();
                queueTimeout = portMAX_DELAY;
                break;
        case States::Running:
                RunningState();
                delta = xTaskGetTickCount() - lastWakeTime;
                if (delta > LV_DISP_DEF_REFR_PERIOD)
                        delta = LV_DISP_DEF_REFR_PERIOD;
                queueTimeout = LV_DISP_DEF_REFR_PERIOD - delta;
                break;
        default:
                queueTimeout = portMAX_DELAY;
                break;
        }

        Messages msg;
        bool messageReceived = xQueueReceive(msgQueue, &msg, queueTimeout);
        lastWakeTime = xTaskGetTickCount();
        if (messageReceived)
        {
                switch (msg)
                {
                case Messages::DimScreen:
                        // Backup brightness is the brightness to return to after dimming or sleeping
                        brightnessController.Backup();
                        brightnessController.Set(Controllers::BrightnessController::Levels::Low);
                        break;

                case Messages::RestoreBrightness:
                        brightnessController.Restore();
                        break;

                case Messages::GoToSleep:
                        while (brightnessController.Level() != Controllers::BrightnessController::Levels::Off)
                        {
                                brightnessController.Lower();
                                vTaskDelay(100);
                        }
                        lcd.DisplayOff();
                        PushMessageToSystemTask(Pinetime::System::Messages::OnDisplayTaskSleeping);
                        state = States::Idle;
                        break;

                case Messages::GoToRunning:
                        lcd.DisplayOn();
                        brightnessController.Restore();
                        state = States::Running;
                        break;

                case Messages::UpdateTimeOut:
                        PushMessageToSystemTask(System::Messages::UpdateTimeOut);
                        break;

                case Messages::UpdateBleConnection:
                        // clockScreen.SetBleConnectionState(bleController.IsConnected() ? Screens::Clock::BleConnectionStates::Connected :
                        // Screens::Clock::BleConnectionStates::NotConnected);
                        break;

                case Messages::NewNotification:
                        // LoadApp(Apps::NotificationsPreview, DisplayApp::FullRefreshDirections::Down);
                        break;

                case Messages::TimerDone:
                        //TODO
                        break;

                case Messages::AlarmTriggered:
                        //TODO
                        break;

                case Messages::TouchEvent:
                        {
                                if (state != States::Running)
                                        break;
                                auto gesture = ConvertGesture(touchHandler.GestureGet());
                                switch (gesture)
                                {
                                case TouchEvents::Tap:
                                        if (_screenGraph->handleTap())
                                                touchHandler.CancelTap();
                                        break;
                                case TouchEvents::LongTap:
                                        if (_screenGraph->handleLongTap())
                                                touchHandler.CancelTap();
                                        break;
                                case TouchEvents::DoubleTap:
                                        if (_screenGraph->handleDoubleTap())
                                                touchHandler.CancelTap();
                                        break;
                                case TouchEvents::SwipeLeft:
                                        _screenGraph->handleSwipe(Screen::SwipeDirection::Left);
                                        touchHandler.CancelTap();
                                        break;
                                case TouchEvents::SwipeRight:
                                        _screenGraph->handleSwipe(Screen::SwipeDirection::Right);
                                        touchHandler.CancelTap();
                                        break;
                                case TouchEvents::SwipeUp:
                                        _screenGraph->handleSwipe(Screen::SwipeDirection::Up);
                                        touchHandler.CancelTap();
                                        break;
                                case TouchEvents::SwipeDown:
                                        _screenGraph->handleSwipe(Screen::SwipeDirection::Down);
                                        touchHandler.CancelTap();
                                        break;
                                default:
                                        break;
                                }
                        }
                        break;

                case Messages::ButtonPushed:
                        _screenGraph->handleButtonPress();
                        break;

                case Messages::BleFirmwareUpdateStarted:
                        _screenGraph->activateScreen(ScreenGraph::ScreenTag::FirmwareUpdate);
                        break;

                case Messages::UpdateDateTime:
                        // Added to remove warning
                        // What should happen here?
                        break;
                }
        }

        // handle touch events
        if (touchHandler.IsTouching())
                _screenGraph->handleTouch(static_cast<int>(touchHandler.GetX()), static_cast<int>(touchHandler.GetY()));
}


void DisplayApp::RunningState()
{
        Screen *currentScreen = _screenGraph->currentScreen();
        if ((!currentScreen || !currentScreen->isRunning()) && _screenGraph)
                _screenGraph->activateScreen(INITIAL_SCREEN);

        if (_screenGraph)
                _screenGraph->handleRefresh();
        lv_task_handler();
}


void DisplayApp::IdleState()
{
}


void DisplayApp::PushMessage(Messages msg)
{
        if (in_isr())
        {
                BaseType_t xHigherPriorityTaskWoken;
                xHigherPriorityTaskWoken = pdFALSE;
                xQueueSendFromISR(msgQueue, &msg, &xHigherPriorityTaskWoken);
                if (xHigherPriorityTaskWoken)
                        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
        else
                xQueueSend(msgQueue, &msg, portMAX_DELAY);
}


void DisplayApp::setFullRefreshDirection(SystemInterface::FullRefreshDirection direction) {
        switch (direction) {
        case SystemInterface::FullRefreshDirection::Down:
                lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::Down);
                break;
        case SystemInterface::FullRefreshDirection::Up:
                lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::Up);
                break;
        case SystemInterface::FullRefreshDirection::Left:
                lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::Left);
                break;
        case SystemInterface::FullRefreshDirection::Right:
                lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::Right);
                break;
//        case DisplayApp::FullRefreshDirections::LeftAnim:
//                lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::LeftAnim);
//                break;
//        case DisplayApp::FullRefreshDirections::RightAnim:
//                lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::RightAnim);
//                break;
        default:
                break;
        }
}


void DisplayApp::PushMessageToSystemTask(Pinetime::System::Messages message)
{
        if (systemTask != nullptr)
                systemTask->PushMessage(message);
}


void DisplayApp::Register(Pinetime::System::SystemTask* systemTask)
{
        this->systemTask = systemTask;
}
