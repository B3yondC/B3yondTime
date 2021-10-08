#include "components/motion/MotionController.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



MotionController::MotionController(QObject *parent)
        : QObject(parent)
{
}


QWidget *MotionController::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_nbStepsLabel)
                return nullptr;

        QLabel *titleLabel = new QLabel("Motion");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        QComboBox *deviceTypeComboBox = new QComboBox();
        deviceTypeComboBox->addItem("Unknown");
        deviceTypeComboBox->addItem("BMA421");
        deviceTypeComboBox->addItem("BMA425");
        deviceTypeComboBox->setCurrentIndex(static_cast<int>(_deviceType));
        connect(deviceTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(mockup_deviceTypeChanged(int)));

        _mockup_nbStepsLabel = new QLabel();
        mockup_updateNbStepsLabel();

        _mockup_nbStepsSlider = new QSlider(Qt::Horizontal);
        _mockup_nbStepsSlider->setRange(0, 50000);
        _mockup_nbStepsSlider->setTracking(true);
        _mockup_nbStepsSlider->setSingleStep(100);
        _mockup_nbStepsSlider->setPageStep(1000);
        _mockup_nbStepsSlider->setValue(static_cast<int>(_nbSteps));
        connect(_mockup_nbStepsSlider, SIGNAL(valueChanged(int)), this, SLOT(setNbSteps(int)));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(new QLabel("Device type"));
        layout->addWidget(deviceTypeComboBox);
        layout->addSpacing(16);
        layout->addWidget(_mockup_nbStepsLabel);
        layout->addWidget(_mockup_nbStepsSlider);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}


void MotionController::setNbSteps(int value)
{
        _nbSteps = static_cast<uint32_t>(value);
        mockup_updateNbStepsLabel();
        if (!_mockup_sliderChanging && _mockup_nbStepsSlider)
        {
                _mockup_sliderChanging = true;
                _mockup_nbStepsSlider->setValue(value);
                _mockup_sliderChanging = false;
        }
}


void MotionController::mockup_updateNbStepsLabel()
{
        if (!_mockup_nbStepsLabel)
                return;

        _mockup_nbStepsLabel->setText(QString("# steps: %1").arg(_nbSteps));
}
