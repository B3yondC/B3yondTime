#ifndef SETTINGS_H
#define SETTINGS_H


#include <cstdint>
#include <bitset>

#include <QObject>
#include <QWidget>

#include "components/brightness/BrightnessController.h"

class QLabel;
class QSlider;
class QComboBox;



namespace Pinetime {
        namespace Controllers {
                class Settings : public QObject
                {
                        Q_OBJECT

                public:

                        enum class WakeUpMode : uint8_t {
                                SingleTap = 0,
                                DoubleTap = 1,
                                RaiseWrist = 2,
                        };

                        Settings(QObject *parent = nullptr);

                        uint32_t GetStepsGoal() const { return _stepsGoal; }
                        void SetStepsGoal(uint32_t value);

                        BrightnessController::Levels GetBrightness() const { return _brightness; }
                        void SetBrightness(BrightnessController::Levels level);

                        std::bitset<3> getWakeUpModes() const { return _wakeUpMode; }
                        bool isWakeUpModeOn(const WakeUpMode mode) const { return getWakeUpModes()[static_cast<size_t>(mode)]; }
                        void setWakeUpMode(WakeUpMode wakeUp, bool enabled);

                        uint8_t GetClockFace() const { return _clockFace; }
                        void SetClockFace(uint8_t face);

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                private:

                        uint32_t _stepsGoal = 1000;
                        BrightnessController::Levels _brightness = BrightnessController::Levels::Medium;
                        std::bitset<3> _wakeUpMode {0};
                        uint8_t _clockFace = 0;

                        QLabel *_mockup_stepsGoalLabel = nullptr;
                        QSlider *_mockup_stepsGoalSlider = nullptr;
                        QComboBox *_mockup_brightnessComboBox = nullptr;
                        bool _mockup_sliderChanging = false;

                        void mockup_updateStepsGoalLabel();

                private slots:

                        void mockup_setStepsGoal(int value) { SetStepsGoal(static_cast<uint32_t>(value)); }
                        void mockup_brightnessChanged(int value) { SetBrightness(static_cast<BrightnessController::Levels>(value)); }
                };
        }
}

#endif // SETTINGS_H
