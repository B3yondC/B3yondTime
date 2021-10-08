#ifndef BRIGHTNESSCONTROLLER_H
#define BRIGHTNESSCONTROLLER_H


#include <cstdint>

#include <QObject>
#include <QWidget>

class QComboBox;



namespace Pinetime
{
        namespace Controllers
        {
                class BrightnessController : public QObject
                {
                        Q_OBJECT

                public:

                        enum class Levels : uint8_t
                        {
                                Off = 0,
                                Low = 1,
                                Medium = 2,
                                High = 3,
                                Automatic = 4
                        };

                        BrightnessController(QObject *parent = nullptr);

                        void Init() { }

                        void Set(Levels level);
                        Levels Level() const { return _level; }
                        void Lower();
                        void Higher();
                        void Step();

                        void Backup() { _backupLevel = _level; }
                        void Restore() { Set(_backupLevel); }

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                private:

                        Levels _level = Levels::High;
                        Levels _backupLevel = Levels::High;

                        QComboBox *_mockup_levelComboBox = nullptr;

                private slots:

                        void mockup_levelChanged(int value) { Set(static_cast<Levels>(value)); }
                };
        }
}

#endif // BRIGHTNESSCONTROLLER_H
