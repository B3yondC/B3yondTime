#include "components/settings/Settings.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



Settings::Settings(QObject *parent)
        : QObject(parent)
{
}


void Settings::SetStepsGoal(uint32_t value)
{
        _stepsGoal = value;
        mockup_updateStepsGoalLabel();
        if (!_mockup_sliderChanging && _mockup_stepsGoalSlider)
        {
                _mockup_sliderChanging = true;
                _mockup_stepsGoalSlider->setValue(static_cast<int>(value));
                _mockup_sliderChanging = false;
        }
}


void Settings::SetBrightness(BrightnessController::Levels level)
{
        if (level != _brightness)
        {
                _brightness = level;
                if (_mockup_brightnessComboBox)
                        _mockup_brightnessComboBox->setCurrentIndex(static_cast<int>(_brightness));
        }
}


void Settings::setWakeUpMode(WakeUpMode wakeUp, bool enabled)
{
        _wakeUpMode.set(static_cast<size_t>(wakeUp), enabled);

        // Handle special behavior
        if (enabled)
        {
                switch (wakeUp)
                {
                case WakeUpMode::SingleTap:
                        _wakeUpMode.set(static_cast<size_t>(WakeUpMode::DoubleTap), false);
                        break;
                case WakeUpMode::DoubleTap:
                        _wakeUpMode.set(static_cast<size_t>(WakeUpMode::SingleTap), false);
                        break;
                default:
                        break;
                }
        }
}


void Settings::SetClockFace(uint8_t face)
{
        if (face != _clockFace)
        {
                _clockFace = face;

                //TODO: update combobox
        }
}


QWidget *Settings::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_stepsGoalLabel)
                return nullptr;

        QLabel *titleLabel = new QLabel("Settings");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        _mockup_stepsGoalLabel = new QLabel();
        mockup_updateStepsGoalLabel();

        _mockup_stepsGoalSlider = new QSlider(Qt::Horizontal);
        _mockup_stepsGoalSlider->setRange(100, 50000);
        _mockup_stepsGoalSlider->setTracking(true);
        _mockup_stepsGoalSlider->setSingleStep(100);
        _mockup_stepsGoalSlider->setPageStep(1000);
        _mockup_stepsGoalSlider->setValue(static_cast<int>(_stepsGoal));
        connect(_mockup_stepsGoalSlider, SIGNAL(valueChanged(int)), this, SLOT(mockup_setStepsGoal(int)));

        _mockup_brightnessComboBox = new QComboBox();
        _mockup_brightnessComboBox->addItem("Off");
        _mockup_brightnessComboBox->addItem("Low");
        _mockup_brightnessComboBox->addItem("Medium");
        _mockup_brightnessComboBox->addItem("High");
        _mockup_brightnessComboBox->addItem("Automatic");
        _mockup_brightnessComboBox->setCurrentIndex(static_cast<int>(_brightness));
        connect(_mockup_brightnessComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(mockup_brightnessChanged(int)));

        //TODO: add widgets for the wake up mode

        //TODO: add widgets for the clock face

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(_mockup_stepsGoalLabel);
        layout->addWidget(_mockup_stepsGoalSlider);
        layout->addSpacing(16);
        layout->addWidget(new QLabel("Brightness"));
        layout->addWidget(_mockup_brightnessComboBox);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}


void Settings::mockup_updateStepsGoalLabel()
{
        if (!_mockup_stepsGoalLabel)
                return;

        _mockup_stepsGoalLabel->setText(QString("Steps goal: %1").arg(_stepsGoal));
}
