#include "Meeting.h"
#include "Date.h"

Meeting::Meeting()
    : sponsor_(), participator_(), startDate_(), endDate_(), title_() {
    // empty
}

Meeting::Meeting(std::string sponsor, std::string participator, \
  Date startTime, Date endTime, std::string title)
    : sponsor_(sponsor), participator_(participator),
      startDate_(startTime), endDate_(endTime), title_(title) {
  // empty
}

std::string Meeting::getSponsor(void) {
  return sponsor_;
}

void Meeting::setSponsor(std::string sponsor) {
  sponsor_ = sponsor;
}

std::string Meeting::getParticipator(void) {
  return participator_;
}

void Meeting::setParticipator(std::string participator) {
  participator_ = participator;
}

Date Meeting::getStartDate(void) {
  return startDate_;
}

void Meeting::setStartDate(Date startTime) {
  startDate_ = startTime;
}

Date Meeting::getEndDate(void) {
  return endDate_;
}

void Meeting::setEndDate(Date endTime) {
  endDate_ = endTime;
}

std::string Meeting::getTitle(void) {
  return title_;
}

void Meeting::setTitle(std::string title) {
  title_ = title;
}
