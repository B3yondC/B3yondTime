#include "FirmwareValidator.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



FirmwareValidator::FirmwareValidator(QObject *parent)
        : QObject(parent)
{
}


QWidget *FirmwareValidator::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_isValidatedCheckBox)
                return nullptr;

        QLabel *titleLabel = new QLabel("Firmware validation");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        _mockup_isValidatedCheckBox = new QCheckBox("Validated");
        _mockup_isValidatedCheckBox->setCheckState(_isValidated ? Qt::Checked : Qt::Unchecked);
        connect(_mockup_isValidatedCheckBox, SIGNAL(stateChanged(int)), this, SLOT(mockup_isValidatedChanged(int)));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(_mockup_isValidatedCheckBox);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}


void FirmwareValidator::Validate()
{
        if (_isValidated)
                return;

        _isValidated = true;
        if (_mockup_isValidatedCheckBox)
                _mockup_isValidatedCheckBox->setCheckState(Qt::Checked);
}


void FirmwareValidator::Reset()
{
        if (!_isValidated)
                return;

        _isValidated = false;
        if (_mockup_isValidatedCheckBox)
                _mockup_isValidatedCheckBox->setCheckState(Qt::Unchecked);
}


void FirmwareValidator::mockup_isValidatedChanged(int state)
{
        if (state == Qt::Checked)
                Validate();
        else
                Reset();
}
