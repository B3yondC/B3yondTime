#ifndef WATCHDOG_H
#define WATCHDOG_H


#include <QObject>
#include <QWidget>



namespace Pinetime
{
        namespace Drivers
        {
                class Watchdog : public QObject
                {
                        Q_OBJECT

                public:

                        enum class ResetReasons
                        {
                                ResetPin,
                                Watchdog,
                                SoftReset,
                                CpuLockup,
                                SystemOff,
                                LpComp,
                                DebugInterface,
                                NFC,
                                HardReset
                        };

                        Watchdog(QObject *parent = nullptr);

                        ResetReasons ResetReason() const { return _resetReason; }

                private:

                        ResetReasons _resetReason = ResetReasons::SoftReset;
                };


                class WatchdogView
                {
                public:

                        WatchdogView(const Watchdog& watchdog)
                                : watchdog { watchdog }
                        {
                        }

                        Watchdog::ResetReasons ResetReason() const { return watchdog.ResetReason(); }

                private:
                        const Watchdog& watchdog;
                };
        }
}

#endif // WATCHDOG_H
