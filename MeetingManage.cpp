#include "MeetingManage.h"
#include "Date.h"
#include "Meeting.h"

bool MeetingManage::instanceFlag_ = false;
MeetingManage* MeetingManage::instance_ = NULL;

MeetingManage::MeetingManage() : meetings_() {}

MeetingManage::~MeetingManage() {
  instance_ = NULL;
  instanceFlag_ = false;
}

MeetingManage* MeetingManage::getInstance() {
  if (!instanceFlag_) {
    instance_ = new MeetingManage();
    instanceFlag_ = true;
  }
  return instance_;
}

void MeetingManage::initMeetingsList(std::list<Meeting> meetings) {
  meetings_ = meetings;
}

std::list<Meeting> MeetingManage::acquireMeetingsList(void) {
  return meetings_;
}

bool MeetingManage::addMeeting(std::string sponsor, std::string participator,
                               Date stime, Date etime, std::string title) {
  // failed if there is only one person in the meeting
  if (sponsor == participator)
    return false;

  // failed if the times are not valid
  if (!(Date::isValid(stime) && Date::isValid(etime) && stime <= etime))
    return false;

  // failed if the meeting exists
  if (queryMeetingByTitle(title) != NULL)
    return false;

  // failed if sponsor or participator is not available
  if (!(queryMeetingsByTime(sponsor, stime, etime).empty())
      || !(queryMeetingsByTime(participator, stime, etime).empty()))
    return false;

  // if all tests are passed, add the meeting
  meetings_.push_back(Meeting(sponsor, participator, stime, etime, title));
  return true;
}

bool MeetingManage::deleteMeeting(std::string userName, std::string title) {
  // search the meeting
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getSponsor() == userName && it->getTitle() == title) {
      meetings_.erase(it);  // delete the meeting when matched
      return true;
    }

  return false;
}

bool MeetingManage::deleteAllMeetings(std::string userName) {
  int count = 0;

  // search the meeting
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getSponsor() == userName) {
      typename std::list<Meeting>::iterator tmpit = it;
      --it;
      meetings_.erase(tmpit);  // delete the meeting when matched
      ++count;
    }

  return count > 0;
}

bool MeetingManage::updateMeetingParticipator(std::string title,
                                              std::string newParticipator) {
  // search for the Meeting
  Meeting *found= queryMeetingByTitle(title);

  if (found!= NULL) {
      if (newParticipator == found->getSponsor())
        return false;  // failed if the participator is the sponsor

      if (!(queryMeetingsByTime(newParticipator, found->getStartDate(),
                            found->getEndDate()).empty()))
        return false;  // failed if the new participator is not available

      found->setParticipator(newParticipator);
      return true;
  } else {
    return false;
  }
}

bool MeetingManage::updateMeetingStartDate(std::string title,
                                           Date newStartDate) {
  // failed if the new start date is invalid
  if (!Date::isValid(newStartDate))
    return false;

  Meeting *found = queryMeetingByTitle(title);
  if (found!= NULL) {
    // failed if the new start date is later than the end date
    if (newStartDate > found->getEndDate())
      return false;

    found->setStartDate(newStartDate);
    return true;
  }

  return false;
}

bool MeetingManage::updateMeetingEndDate(std::string title, Date newEndDate) {
  // failed if the new end date is invalid
  if (!Date::isValid(newEndDate))
    return false;

  Meeting *found= queryMeetingByTitle(title);
  if (found!= NULL) {
    // failed if the new end date is ealier than the start date
    if (newEndDate < found->getStartDate())
      return false;

    found->setEndDate(newEndDate);
    return true;
  }

  return false;
}

Meeting* MeetingManage::queryMeetingByTitle(std::string title) {
  // search the meeting
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getTitle() == title) {
      return &(*it);
    }

  return NULL;
}

std::list<Meeting> MeetingManage::queryMeetingsByTime(std::string userName,
    Date stime, Date etime) {
  std::list<Meeting> found;  // empty list

  if (stime > etime)
    return found;

  // search for the meetings
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getSponsor() == userName || it->getParticipator() == userName) {
      if (it->getStartDate() >= stime && it->getEndDate() <= etime)
        found.push_back(*it);
      else if (it->getStartDate() <= etime && it->getEndDate() >= etime)
        found.push_back(*it);
      else if (it->getStartDate() <= stime && it->getEndDate() >= stime)
        found.push_back(*it);
    }

  return found;
}

std::list<Meeting> MeetingManage::listAllMeetings(std::string userName) {
  std::list<Meeting> found;  // empty list

  // search for the meetings
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getSponsor() == userName || it->getParticipator() == userName)
        found.push_back(*it);

  return found;
}

std::list<Meeting> MeetingManage::listAllSponsorMeetings(
    std::string userName) {
  std::list<Meeting> found;  // empty list

  // search for the meetings
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getSponsor() == userName)
        found.push_back(*it);

  return found;
}

std::list<Meeting> MeetingManage::listAllParticipateMeetings(
    std::string userName) {
  std::list<Meeting> found;  // empty list

  // search for the meetings
  for (typename std::list<Meeting>::iterator it = meetings_.begin();
       it != meetings_.end(); ++it)
    if (it->getParticipator() == userName)
        found.push_back(*it);

  return found;
}
