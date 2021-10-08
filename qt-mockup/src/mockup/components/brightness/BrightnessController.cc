#include "BrightnessController.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



BrightnessController::BrightnessController(QObject *parent)
        : QObject(parent)
{
}


void BrightnessController::Set(Levels level)
{
        if (level == _level)
                return;

        _level = level;
        if (_mockup_levelComboBox)
                _mockup_levelComboBox->setCurrentIndex(static_cast<int>(_level));
}


void BrightnessController::Lower()
{
        switch (_level)
        {
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


void BrightnessController::Higher()
{
        switch (_level)
        {
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


void BrightnessController::Step()
{
        switch (_level)
        {
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


QWidget *BrightnessController::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_levelComboBox)
                return nullptr;

        QLabel *titleLabel = new QLabel("Brightness");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        _mockup_levelComboBox = new QComboBox();
        _mockup_levelComboBox->addItem("Off");
        _mockup_levelComboBox->addItem("Low");
        _mockup_levelComboBox->addItem("Medium");
        _mockup_levelComboBox->addItem("High");
        _mockup_levelComboBox->setCurrentIndex(static_cast<int>(_level));
        connect(_mockup_levelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(mockup_levelChanged(int)));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(new QLabel("Current level"));
        layout->addWidget(_mockup_levelComboBox);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}
