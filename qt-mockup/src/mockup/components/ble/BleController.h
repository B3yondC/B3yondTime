#ifndef BLE_H
#define BLE_H


#include <array>
#include <cstdint>

#include <QObject>
#include <QWidget>

class QComboBox;



namespace Pinetime {
        namespace Controllers {
                class Ble : public QObject
                {
                        Q_OBJECT

                public:

                        using BleAddress = std::array<uint8_t, 6>;

                        enum class FirmwareUpdateStates : int
                        {
                                Idle = 0,
                                Running = 1,
                                Validated = 2,
                                Error = 3
                        };


                        Ble(QObject *parent = nullptr);

                        const BleAddress& Address() const { return _address; }
                        bool IsConnected() const { return _isConnected; }

                        void Connect() { _isConnected = true; }
                        void Disconnect() { _isConnected = false; }

                        void StartFirmwareUpdate();
                        void StopFirmwareUpdate();
                        void FirmwareUpdateTotalBytes(uint32_t totalBytes) { _totalBytes = totalBytes; }
                        void FirmwareUpdateCurrentBytes(uint32_t currentBytes) { _currentBytes = currentBytes; }
                        void State(FirmwareUpdateStates state) { _state = state; }

                        bool IsFirmwareUpdating() const { return _isFirmwareUpdating; }
                        uint32_t FirmwareUpdateTotalBytes() const { return _totalBytes; }
                        uint32_t FirmwareUpdateCurrentBytes() const { return _currentBytes; }
                        FirmwareUpdateStates State() const { return _state; }

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                public slots:

                        void mockup_setConnected(bool value) { _isConnected = value; }
                        void mockup_setIsFwUpdating(bool value) { _isFirmwareUpdating = value; }
                        void mockup_setFwUpdateProgress(int percentComplete);
                        void mockup_setFwUpdateStatus(int value) { State(static_cast<FirmwareUpdateStates>(value)); }

                private:

                        BleAddress _address;
                        bool _isConnected = false;
                        bool _isFirmwareUpdating = false;
                        FirmwareUpdateStates _state = FirmwareUpdateStates::Idle;
                        uint32_t _totalBytes = 10000;
                        uint32_t _currentBytes = 0;

                        QComboBox *_mockup_fwUpdateStatusComboBox = nullptr;

                private slots:

                        void mockup_connectedStateChanged(int state);
                        void mockup_fwUpdatingStateChanged(int state);
                };
        }
}

#endif // BLE_H
