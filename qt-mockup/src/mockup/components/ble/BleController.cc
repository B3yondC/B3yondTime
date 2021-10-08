#include "components/ble/BleController.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



Ble::Ble(QObject *parent)
        : QObject(parent)
{
        for (int i = 0; i < 6; i++)
                _address[i] = ((0xa + i) << 4) + i;
}


QWidget *Ble::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_fwUpdateStatusComboBox)
                return nullptr;

        QLabel *titleLabel = new QLabel("BLE");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        QCheckBox *connectedCheckBox = new QCheckBox("Connected");
        connectedCheckBox->setCheckState(_isConnected ? Qt::Checked : Qt::Unchecked);
        connect(connectedCheckBox, SIGNAL(stateChanged(int)), this, SLOT(mockup_connectedStateChanged(int)));

        QCheckBox *firmwareUpdatingCheckBox = new QCheckBox("FW updating");
        firmwareUpdatingCheckBox->setCheckState(_isFirmwareUpdating ? Qt::Checked : Qt::Unchecked);
        connect(firmwareUpdatingCheckBox, SIGNAL(stateChanged(int)), this, SLOT(mockup_fwUpdatingStateChanged(int)));

        _mockup_fwUpdateStatusComboBox = new QComboBox();
        _mockup_fwUpdateStatusComboBox->addItem("Idle");
        _mockup_fwUpdateStatusComboBox->addItem("Running");
        _mockup_fwUpdateStatusComboBox->addItem("Validated");
        _mockup_fwUpdateStatusComboBox->addItem("Error");
        _mockup_fwUpdateStatusComboBox->setCurrentIndex(static_cast<int>(_state));
        mockup_fwUpdatingStateChanged(firmwareUpdatingCheckBox->checkState());
        connect(_mockup_fwUpdateStatusComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(mockup_setFwUpdateStatus(int)));

        QSlider *updateProgressSlider = new QSlider(Qt::Horizontal);
        updateProgressSlider->setRange(0, 100);
        updateProgressSlider->setTracking(true);
        updateProgressSlider->setSingleStep(1);
        updateProgressSlider->setPageStep(10);
        connect(updateProgressSlider, SIGNAL(valueChanged(int)), this, SLOT(mockup_setFwUpdateProgress(int)));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(connectedCheckBox);
        layout->addWidget(firmwareUpdatingCheckBox);
        layout->addWidget(new QLabel("Update status"));
        layout->addWidget(_mockup_fwUpdateStatusComboBox);
        layout->addWidget(new QLabel("Update progress"));
        layout->addWidget(updateProgressSlider);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}


void Ble::mockup_setFwUpdateProgress(int percentComplete)
{
         _currentBytes = _totalBytes * static_cast<uint32_t>(percentComplete) / 100;
}


void Ble::mockup_connectedStateChanged(int state)
{
        mockup_setConnected(state == Qt::Checked);
}


void Ble::mockup_fwUpdatingStateChanged(int state)
{
        mockup_setIsFwUpdating(state == Qt::Checked);
        if (_mockup_fwUpdateStatusComboBox)
        {
                if (!_isFirmwareUpdating)
                {
                        _mockup_fwUpdateStatusComboBox->setCurrentIndex(0);
                        _mockup_fwUpdateStatusComboBox->setEnabled(false);
                }
                else
                        _mockup_fwUpdateStatusComboBox->setEnabled(true);
        }
}
