#include "components/datetime/DateTimeController.h"

#include <QtCore>
#include <QtWidgets>


using namespace Pinetime::Controllers;



char const* DateTime::_daysString[] = {"--", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
char const* DateTime::_daysStringLow[] = {"--", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
char const* DateTime::_daysStringShort[] = {"--", "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
char const* DateTime::_daysStringShortLow[] = {"--", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

char const* DateTime::_monthsString[] = { "--", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
char const* DateTime::_monthsStringLow[] = { "--", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char const* DateTime::_monthsStringShort[] = {"--", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
char const* DateTime::_monthsStringShortLow[] = {"--", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


DateTime::DateTime(QObject *parent)
        : QObject(parent)
{
        UpdateTime(0);
        _startTime = std::chrono::system_clock::now();
}


std::chrono::seconds DateTime::Uptime() const
{
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime);
}


void DateTime::SetTime(uint16_t year, uint8_t month, uint8_t day, uint8_t dayOfWeek, uint8_t hour, uint8_t minute, uint8_t second, uint32_t systickCounter)
{
        (void)year;
        (void)month;
        (void)day;
        (void)dayOfWeek;
        (void)hour;
        (void)minute;
        (void)second;
        (void)systickCounter;
}


void DateTime::UpdateTime(uint32_t systickCounter)
{
        (void)systickCounter;

        if (!_mockup_isUpdating)
                return;

        QDateTime now = QDateTime::currentDateTime();
        _year = static_cast<uint16_t>(now.date().year());
        _month = static_cast<Months>(now.date().month());
        _day = static_cast<uint8_t>(now.date().day());
        _dayOfWeek = static_cast<Days>(now.date().dayOfWeek());
        _hour = static_cast<uint8_t>(now.time().hour());
        _minute = static_cast<uint8_t>(now.time().minute());
        _second = static_cast<uint8_t>(now.time().second());

        if (_mockup_dateTimeEdit)
                _mockup_dateTimeEdit->setDateTime(now);
}


QWidget *DateTime::mockup_createWidget(QWidget *parent)
{
        // can only be called once...
        if (_mockup_dateTimeEdit)
                return nullptr;

        QLabel *titleLabel = new QLabel("Date & Time");
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setItalic(true);
        titleLabel->setFont(titleFont);

        QCheckBox *updatingCheckBox = new QCheckBox("Sync to real time");
        updatingCheckBox->setCheckState(_mockup_isUpdating ? Qt::Checked : Qt::Unchecked);
        connect(updatingCheckBox, SIGNAL(stateChanged(int)), this, SLOT(mockup_updatingStateChanged(int)));

        _mockup_dateTimeEdit = new QDateTimeEdit();
        _mockup_dateTimeEdit->setCalendarPopup(true);
        _mockup_dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
        _mockup_dateTimeEdit->setReadOnly(_mockup_isUpdating);
        connect(_mockup_dateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(mockup_setDateTime(const QDateTime &)));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(titleLabel);
        layout->addWidget(updatingCheckBox);
        layout->addWidget(_mockup_dateTimeEdit);
        layout->addStretch(1);

        QWidget *container = new QWidget(parent);
        container->setLayout(layout);
        return container;
}


void DateTime::mockup_setIsUpdating(bool value)
{
        _mockup_isUpdating = value;
        if (_mockup_dateTimeEdit)
                _mockup_dateTimeEdit->setReadOnly(value);
}


void DateTime::mockup_setDateTime(const QDateTime &value)
{
        // ignore when synced to real time
        if (_mockup_isUpdating)
                return;

        _year = static_cast<uint16_t>(value.date().year());
        _month = static_cast<Months>(value.date().month());
        _day = static_cast<uint8_t>(value.date().day());
        _dayOfWeek = static_cast<Days>(value.date().dayOfWeek());
        _hour = static_cast<uint8_t>(value.time().hour());
        _minute = static_cast<uint8_t>(value.time().minute());
        _second = static_cast<uint8_t>(value.time().second());
}


void DateTime::mockup_updatingStateChanged(int state)
{
        mockup_setIsUpdating(state == Qt::Checked);
}
