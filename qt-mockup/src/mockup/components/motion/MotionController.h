#ifndef MOTION_H
#define MOTION_H


#include <cstdint>

#include <QObject>
#include <QWidget>

class QLabel;
class QSlider;



namespace Pinetime {
        namespace Controllers {
                class MotionController : public QObject
                {
                        Q_OBJECT

                public:

                        enum class DeviceTypes : int
                        {
                                Unknown = 0,
                                BMA421 = 1,
                                BMA425 = 2,
                        };


                        MotionController(QObject *parent = nullptr);

                        DeviceTypes DeviceType() const { return _deviceType; }

                        uint32_t NbSteps() const { return _nbSteps; }

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                public slots:

                        void setNbSteps(int value);

                private:

                        DeviceTypes _deviceType = DeviceTypes::BMA421;
                        uint32_t _nbSteps = 250;

                        QLabel *_mockup_nbStepsLabel = nullptr;
                        QSlider *_mockup_nbStepsSlider = nullptr;
                        bool _mockup_sliderChanging = false;

                        void mockup_updateNbStepsLabel();

                private slots:

                        void mockup_deviceTypeChanged(int index) { _deviceType = static_cast<DeviceTypes>(index); }
                };
        }
}

#endif // MOTION_H
