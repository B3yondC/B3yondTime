#ifndef FIRMWAREVALIDATOR_H
#define FIRMWAREVALIDATOR_H


#include <cstdint>

#include <QObject>
#include <QWidget>

class QCheckBox;



namespace Pinetime
{
        namespace Controllers
        {
                class FirmwareValidator : public QObject
                {
                        Q_OBJECT

                public:

                        FirmwareValidator(QObject *parent = nullptr);

                        bool IsValidated() const { return _isValidated; }

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                public slots:

                        void Validate();
                        void Reset();

                private:

                        bool _isValidated = false;

                        QCheckBox *_mockup_isValidatedCheckBox = nullptr;

                private slots:

                        void mockup_isValidatedChanged(int state);
                };
        }
}

#endif // FIRMWAREVALIDATOR_H
