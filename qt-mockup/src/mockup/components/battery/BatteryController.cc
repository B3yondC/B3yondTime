#include "components/battery/BatteryController.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



Battery::Battery(QObject *parent)
        : QObject(parent)
{
}


QWidget *Battery::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_chargingCheckBox)
                return nullptr;

        QLabel *titleLabel = new QLabel("Battery");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        _mockup_chargingCheckBox = new QCheckBox("Charging");
        _mockup_chargingCheckBox->setCheckState(_isCharging ? Qt::Checked : Qt::Unchecked);
        connect(_mockup_chargingCheckBox, SIGNAL(stateChanged(int)), this, SLOT(mockup_chargingChanged(int)));

        QCheckBox *powerPresentCheckBox = new QCheckBox("Power present");
        powerPresentCheckBox->setCheckState(_isPowerPresent ? Qt::Checked : Qt::Unchecked);
        connect(powerPresentCheckBox, SIGNAL(stateChanged(int)), this, SLOT(mockup_powerPresentChanged(int)));

        _mockup_voltageLabel = new QLabel();
        mockup_updateVoltageLabel();

        _mockup_voltageSlider = new QSlider(Qt::Horizontal);
        _mockup_voltageSlider->setRange(1000, 4000);
        _mockup_voltageSlider->setTracking(true);
        _mockup_voltageSlider->setSingleStep(10);
        _mockup_voltageSlider->setPageStep(100);
        _mockup_voltageSlider->setValue(static_cast<int>(_voltage));
        connect(_mockup_voltageSlider, SIGNAL(valueChanged(int)), this, SLOT(setVoltage(int)));

        _mockup_percentageSlider = new QSlider(Qt::Horizontal);
        _mockup_percentageSlider->setRange(0, 100);
        _mockup_percentageSlider->setTracking(true);
        _mockup_percentageSlider->setSingleStep(1);
        _mockup_percentageSlider->setPageStep(10);
        _mockup_percentageSlider->setValue(static_cast<int>(_percentRemaining));
        connect(_mockup_percentageSlider, SIGNAL(valueChanged(int)), this, SLOT(setPercentRemaining(int)));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(_mockup_chargingCheckBox);
        layout->addWidget(powerPresentCheckBox);
        layout->addWidget(_mockup_voltageLabel);
        layout->addWidget(_mockup_voltageSlider);
        layout->addWidget(new QLabel("Percent remaining"));
        layout->addWidget(_mockup_percentageSlider);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}


void Battery::setPercentRemaining(int value)
{
        _percentRemaining = static_cast<uint8_t>(value);
        if (!_mockup_sliderChanging && _mockup_percentageSlider)
        {
                _mockup_sliderChanging = true;
                _mockup_percentageSlider->setValue(value);
                _mockup_sliderChanging = false;
        }
}


void Battery::setVoltage(int value)
{
         _voltage = static_cast<uint16_t>(value);
         mockup_updateVoltageLabel();
         if (!_mockup_sliderChanging && _mockup_voltageSlider)
         {
                 _mockup_sliderChanging = true;
                 _mockup_voltageSlider->setValue(value);
                 _mockup_sliderChanging = false;
         }
}


void Battery::mockup_updateVoltageLabel()
{
        if (!_mockup_voltageLabel)
                return;

        _mockup_voltageLabel->setText(QString("Voltage: %1V").arg(static_cast<double>(_voltage) * 0.001, 0, 'f', 3));
}


void Battery::mockup_chargingChanged(int state)
{
        setIsCharging(state == Qt::Checked);
}


void Battery::mockup_powerPresentChanged(int state)
{
        setIsPowerPresent(state == Qt::Checked);
        if (_mockup_chargingCheckBox)
        {
                if (_isPowerPresent)
                        _mockup_chargingCheckBox->setEnabled(true);
                else
                {
                        _mockup_chargingCheckBox->setChecked(Qt::Unchecked);
                        _mockup_chargingCheckBox->setEnabled(false);
                }
        }
}
