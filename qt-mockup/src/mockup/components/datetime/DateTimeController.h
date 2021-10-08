#ifndef DATETIME_H
#define DATETIME_H


#include <cstdint>
#include <chrono>

#include <QObject>
#include <QWidget>

class QDateTimeEdit;



namespace Pinetime {
        namespace Controllers {
                class DateTime : public QObject
                {
                        Q_OBJECT

                public:

                        enum class Days : uint8_t
                        {
                                Unknown,
                                Monday,
                                Tuesday,
                                Wednesday,
                                Thursday,
                                Friday,
                                Saturday,
                                Sunday
                        };

                        enum class Months : uint8_t
                        {
                                Unknown,
                                January,
                                February,
                                March,
                                April,
                                May,
                                June,
                                July,
                                August,
                                September,
                                October,
                                November,
                                December
                        };

                        DateTime(QObject *parent = nullptr);

                        uint16_t Year() const { return _year; }
                        Months Month() const { return _month; }
                        uint8_t Day() const { return _day; }
                        Days DayOfWeek() const { return _dayOfWeek; }
                        uint8_t Hours() const { return _hour; }
                        uint8_t Minutes() const { return _minute; }
                        uint8_t Seconds() const { return _second; }

                        std::chrono::seconds Uptime() const;

                        const char* MonthToString() { return _monthsString[static_cast<uint8_t>(_month)]; }
                        const char* MonthToStringLow() { return _monthsStringLow[static_cast<uint8_t>(_month)]; }
                        const char* MonthShortToString() { return _monthsStringShort[static_cast<uint8_t>(_month)]; }
                        const char* MonthShortToStringLow() { return _monthsStringShortLow[static_cast<uint8_t>(_month)]; }
                        const char* DayOfWeekToString() { return _daysString[static_cast<uint8_t>(_dayOfWeek)]; }
                        const char* DayOfWeekToStringLow() { return _daysStringLow[static_cast<uint8_t>(_dayOfWeek)]; }
                        const char* DayOfWeekShortToString() { return _daysStringShort[static_cast<uint8_t>(_dayOfWeek)]; }
                        const char* DayOfWeekShortToStringLow() { return _daysStringShortLow[static_cast<uint8_t>(_dayOfWeek)]; }

                        static const char* MonthToString(Months month) { return _monthsString[static_cast<uint8_t>(month)]; }
                        static const char* MonthToStringLow(Months month) { return _monthsStringLow[static_cast<uint8_t>(month)]; }
                        static const char* MonthShortToString(Months month) { return _monthsStringShort[static_cast<uint8_t>(month)]; }
                        static const char* MonthShortToStringLow(Months month) { return _monthsStringShortLow[static_cast<uint8_t>(month)]; }
                        static const char* DayOfWeekToString(Days dayOfWeek) { return _daysString[static_cast<uint8_t>(dayOfWeek)]; }
                        static const char* DayOfWeekToStringLow(Days dayOfWeek) { return _daysStringLow[static_cast<uint8_t>(dayOfWeek)]; }
                        static const char* DayOfWeekShortToString(Days dayOfWeek) { return _daysStringShort[static_cast<uint8_t>(dayOfWeek)]; }
                        static const char* DayOfWeekShortToStringLow(Days dayOfWeek) { return _daysStringShortLow[static_cast<uint8_t>(dayOfWeek)]; }

                        void SetTime(uint16_t Year,
                                     uint8_t Month,
                                     uint8_t Day,
                                     uint8_t DayOfWeek,
                                     uint8_t Hours,
                                     uint8_t Minutes,
                                     uint8_t Seconds,
                                     uint32_t systickCounter);

                        void UpdateTime(uint32_t systickCounter);

                        QWidget *mockup_createWidget(QWidget *parent = nullptr);

                public slots:

                        void mockup_setDateTime(const QDateTime &value);
                        void mockup_setIsUpdating(bool value);

                private:

                        uint16_t _year = 0;
                        Months _month = Months::Unknown;
                        uint8_t _day = 0;
                        Days _dayOfWeek = Days::Unknown;
                        uint8_t _hour = 0;
                        uint8_t _minute = 0;
                        uint8_t _second = 0;
                        std::chrono::time_point<std::chrono::system_clock> _startTime;

                        bool _mockup_isUpdating = true;
                        QDateTimeEdit *_mockup_dateTimeEdit = nullptr;

                        static char const* _daysString[];
                        static char const* _daysStringLow[];
                        static char const* _daysStringShort[];
                        static char const* _daysStringShortLow[];
                        static char const* _monthsString[];
                        static char const* _monthsStringLow[];
                        static char const* _monthsStringShort[];
                        static char const* _monthsStringShortLow[];

                private slots:

                        void mockup_updatingStateChanged(int state);
                };
        }
}

#endif // DATETIME_H
