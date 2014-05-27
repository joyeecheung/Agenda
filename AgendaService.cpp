#include "AgendaService.h"
#include "Encode.h"

AgendaService::AgendaService() {
  userManage_ = UserManage::getInstance();
  meetingManage_ = MeetingManage::getInstance();
  fileManage_ = FileManage::getInstance();
}

AgendaService::~AgendaService() {
  delete userManage_;
  delete meetingManage_;
  delete fileManage_;
}

User * AgendaService::userLogIn(std::string userName, std::string password) {
  User *userptr = userManage_->findUserByName(userName);

  if (userptr != NULL)
    if (userptr->getPassword() == encode(password))
      return userptr;

  return NULL;
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
  return userManage_->createUser(userName, encode(password), email, phone);
}

bool AgendaService::deleteUser(User user) {
  // failed if the user doesn't exist
  if (!userManage_->findUserByName(user.getName()))
    return false;

  // failed if the user has sponsor or participate meetings
  if (!meetingManage_->listAllMeetings(user.getName()).empty())
    return false;
  /*
  // delete all meetings the user sponsors
  meetingManage_->deleteAllMeetings(user.getName());

  // delete all meetings the user participates
  std::list<Meeting> pMeetings
    = meetingManage_->listAllParticipateMeetings(user.getName());
  for (typename std::list<Meeting>::iterator it = pMeetings.begin();
       it != pMeetings.end(); ++it)
    meetingManage_->deleteMeeting(it->getSponsor(), it->getTitle());
*/

  // delete the user
  return userManage_->deleteUser(user);
}

std::list<User> AgendaService::listAllUsers(void) {
  return userManage_->listAllUsers();
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                   std::string participator, std::string startTime,
                   std::string endTime) {
  if (userManage_->findUserByName(userName) == NULL
      || userManage_->findUserByName(participator) == NULL)
    return false;

  return meetingManage_->addMeeting(userName, participator,
                                    Date::stringToDate(startTime),
                                    Date::stringToDate(endTime), title);
}

Meeting * AgendaService::meetingQuery(std::string title) {
  return meetingManage_->queryMeetingByTitle(title);
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string startDate,
                                               std::string endDate) {
  return meetingManage_->queryMeetingsByTime(userName,
                                             Date::stringToDate(startDate),
                                             Date::stringToDate(endDate));
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  return meetingManage_->listAllMeetings(userName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(
    std::string userName) {
  return meetingManage_->listAllSponsorMeetings(userName);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
    std::string userName) {
  return meetingManage_->listAllParticipateMeetings(userName);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  return meetingManage_->deleteMeeting(userName, title);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
  return meetingManage_->deleteAllMeetings(userName);
}

void AgendaService::startAgenda(void) {
  userManage_->initUsersList(fileManage_->readUsersFromFile());
  meetingManage_->initMeetingsList(fileManage_->readMeetingsFromFile());
}

void AgendaService::quitAgenda(void) {
  fileManage_->writeUsersToFile(userManage_->listAllUsers());
  fileManage_->writeMeetingsToFile(meetingManage_->acquireMeetingsList());
}
