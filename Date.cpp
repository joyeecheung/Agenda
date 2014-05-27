#include "Date.h"
#include <iomanip>
#include <sstream>

Date::Date() {}

Date::Date(int year, int month, int day, int hour, int minute)
    : year_(year), month_(month), day_(day), hour_(hour), minute_(minute) {
}

int Date::getYear(void) const {
  return year_;
}

void Date::setYear(int year) {
  year_ = year;
}

int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
}

int Date::getDay(void) const {
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

bool Date::isValid(Date date) {
  // limits of days in months
  int limit[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // test if  it's a leap year
  if ((date.year_ % 4 == 0 && date.year_ % 100 != 0) || date.year_ % 400 == 0)
    limit[1] = 29;  // Feb. in leap year should have 29 days

  if (date.month_ < 1 || date.month_ > 12)  // month: 1~12?
    return false;

  // day: match the month?
  if (date.day_ < 1 || date.day_ > limit[date.month_ - 1])
    return false;

  if (date.hour_ < 0 || date.hour_ > 23)  // hour: 0~23?
    return false;

  if (date.minute_ < 0 || date.minute_ > 59)  // minute: 0~59?
    return false;

  return true;
}

Date Date::stringToDate(std::string dateString) {
  int year, month, day, hour, minute;  // used to construct the Date

  // replace seperators with spaces
  for (size_t i = 0; i < dateString.size(); ++i)
    if (dateString[i] > '9' || dateString[i] < '0')
      dateString[i] = ' ';

  std::stringstream ss;  // string stream
  ss << dateString;
  ss >> year >> month >> day >> hour >> minute;

  return Date(year, month, day, hour, minute);
}

std::string Date::dateToString(Date date) {
  std::stringstream ss;  // string stream

  ss << std::setfill('0') << std::setw(4) << date.year_ << '-'
      << std::setw(2) << date.month_ << '-'
      << std::setw(2) << date.day_ << '/'
      << std::setw(2) << date.hour_ << ':'
      << std::setw(2) << date.minute_;

  return ss.str();
}

Date &Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;

  return *this;
}

bool Date::operator==(const Date& date) const {
  return (year_ == date.year_
          && month_ == date.month_
          && day_ == date.day_
          && hour_ == date.hour_
          && minute_ == date.minute_);
}

bool Date::operator>(const Date& date) const {
  if (year_ < date.year_)
    return false;
  if (year_ > date.year_)
    return true;
  if (month_ < date.month_)
    return false;
  if (month_ > date.month_)
    return true;
  if (day_ < date.day_)
    return false;
  if (day_ > date.day_)
    return true;
  if (hour_ < date.hour_)
    return false;
  if (hour_ > date.hour_)
    return true;
  if (minute_ < date.minute_)
    return false;
  if (minute_ > date.minute_)
    return true;

  return false;
}

bool Date::operator<(const Date& date) const {
  return !(*this > date || *this == date);
}

bool Date::operator>=(const Date& date) const {
  return !(*this < date);
}

bool Date::operator<=(const Date& date) const {
  return !(*this > date);
}
