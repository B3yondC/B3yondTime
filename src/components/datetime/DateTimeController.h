#pragma once

#include <cstdint>
#include <chrono>

namespace Pinetime {
  namespace System {
    class SystemTask;
  }
  namespace Controllers {
    class DateTime {
    public:
      enum class Days : uint8_t { Unknown, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
      enum class Months : uint8_t {
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

      void SetTime(uint16_t year,
                   uint8_t month,
                   uint8_t day,
                   uint8_t dayOfWeek,
                   uint8_t hour,
                   uint8_t minute,
                   uint8_t second,
                   uint32_t systickCounter);
      void UpdateTime(uint32_t systickCounter);
      uint16_t Year() const {
        return year;
      }
      Months Month() const {
        return month;
      }
      uint8_t Day() const {
        return day;
      }
      Days DayOfWeek() const {
        return dayOfWeek;
      }
      uint8_t Hours() const {
        return hour;
      }
      uint8_t Minutes() const {
        return minute;
      }
      uint8_t Seconds() const {
        return second;
      }

      const char* MonthToString() { return _monthsString[static_cast<uint8_t>(month)]; }
      const char* MonthToStringLow() { return _monthsStringLow[static_cast<uint8_t>(month)]; }
      const char* MonthShortToString() { return _monthsStringShort[static_cast<uint8_t>(month)]; }
      const char* MonthShortToStringLow() { return _monthsStringShortLow[static_cast<uint8_t>(month)]; }
      const char* DayOfWeekToString() { return _daysString[static_cast<uint8_t>(dayOfWeek)]; }
      const char* DayOfWeekToStringLow() { return _daysStringLow[static_cast<uint8_t>(dayOfWeek)]; }
      const char* DayOfWeekShortToString() { return _daysStringShort[static_cast<uint8_t>(dayOfWeek)]; }
      const char* DayOfWeekShortToStringLow() { return _daysStringShortLow[static_cast<uint8_t>(dayOfWeek)]; }

      static const char* MonthToString(Months month) { return _monthsString[static_cast<uint8_t>(month)]; }
      static const char* MonthToStringLow(Months month) { return _monthsStringLow[static_cast<uint8_t>(month)]; }
      static const char* MonthShortToString(Months month) { return _monthsStringShort[static_cast<uint8_t>(month)]; }
      static const char* MonthShortToStringLow(Months month) { return _monthsStringShortLow[static_cast<uint8_t>(month)]; }
      static const char* DayOfWeekToString(Days dayOfWeek) { return _daysString[static_cast<uint8_t>(dayOfWeek)]; }
      static const char* DayOfWeekToStringLow(Days dayOfWeek) { return _daysStringLow[static_cast<uint8_t>(dayOfWeek)]; }
      static const char* DayOfWeekShortToString(Days dayOfWeek) { return _daysStringShort[static_cast<uint8_t>(dayOfWeek)]; }
      static const char* DayOfWeekShortToStringLow(Days dayOfWeek) { return _daysStringShortLow[static_cast<uint8_t>(dayOfWeek)]; }

      std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> CurrentDateTime() const {
        return currentDateTime;
      }
      std::chrono::seconds Uptime() const {
        return uptime;
      }

      void Register(System::SystemTask* systemTask);
      void SetCurrentTime(std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> t);

    private:
      uint16_t year = 0;
      Months month = Months::Unknown;
      uint8_t day = 0;
      Days dayOfWeek = Days::Unknown;
      uint8_t hour = 0;
      uint8_t minute = 0;
      uint8_t second = 0;

      uint32_t previousSystickCounter = 0;
      std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> currentDateTime;
      std::chrono::seconds uptime {0};

      bool isMidnightAlreadyNotified = false;
      System::SystemTask* systemTask = nullptr;

      static char const* _daysString[];
      static char const* _daysStringLow[];
      static char const* _daysStringShort[];
      static char const* _daysStringShortLow[];
      static char const* _monthsString[];
      static char const* _monthsStringLow[];
      static char const* _monthsStringShort[];
      static char const* _monthsStringShortLow[];
    };
  }
}
