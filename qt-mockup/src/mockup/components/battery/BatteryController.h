#ifndef BATTERY_H
#define BATTERY_H


#include <cstdint>

#include <QObject>
#include <QWidget>

class QCheckBox;
class QLabel;
class QSlider;



namespace Pinetime {
        namespace Controllers {
                class Battery : public QObject
                {
                        Q_OBJECT

                public:

                        Battery(QObject *parent = nullptr);

                        uint8_t PercentRemaining() const { return _percentRemaining; }
                        uint16_t Voltage() const { return _voltage; }
                        bool IsCharging() const { return _isCharging; }
                        bool IsPowerPresent() const { return _isPowerPresent; }

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                public slots:

                        void setPercentRemaining(int value);
                        void setVoltage(int value);
                        void setIsCharging(bool value) { _isCharging = value; }
                        void setIsPowerPresent(bool value) { _isPowerPresent = value; }

                private:

                        uint8_t _percentRemaining = 30;
                        uint16_t _voltage = 3700;
                        bool _isCharging = true;
                        bool _isPowerPresent = true;

                        QCheckBox *_mockup_chargingCheckBox = nullptr;
                        QLabel *_mockup_voltageLabel = nullptr;
                        QSlider *_mockup_voltageSlider = nullptr;
                        QSlider *_mockup_percentageSlider = nullptr;
                        bool _mockup_sliderChanging = false;

                        void mockup_updateVoltageLabel();

                private slots:

                        void mockup_chargingChanged(int state);
                        void mockup_powerPresentChanged(int state);
                };
        }
}

#endif // BATTERY_H
