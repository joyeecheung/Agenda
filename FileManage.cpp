#include "FileManage.h"
#include <fstream>
#include <iomanip>
#include "Date.h"

bool FileManage::instanceFlag_ = false;
FileManage* FileManage::instance_ = NULL;

FileManage::FileManage() : userFileName_(), meetingFileName_() {}

FileManage::~FileManage() {
  instance_ = NULL;
  instanceFlag_ = false;
}

FileManage* FileManage::getInstance(void) {
  if (!instanceFlag_) {
    instance_ = new FileManage();
    instanceFlag_ = true;
  }

  return instance_;
}

std::list<User> FileManage::readUsersFromFile(void) {
  std::ifstream in("user.dat", std::ifstream::in);

  std::list<User> users;  // create an empty list

  if (in) {
    std::string name, password, email, phone;  // stores read data

    if (!in.eof())
      in >> name >> password >> email >> phone;

    while (in && !in.eof()) {
      User tmpUser(name, password, email, phone);
      users.push_back(tmpUser);

      in >> name >> password >> email >> phone;
    }
  }

  return users;
}

void FileManage::writeUsersToFile(std::list<User> users) {
  std::ofstream out("user.dat", std::ifstream::out);

  if (out) {
    while (!users.empty()) {
     out << std::setfill(' ') << std::setw(20) << users.front().getName()
         << std::setw(20) << users.front().getPassword()
         << std::setw(20) << users.front().getEmail()
         << std::setw(20) << users.front().getPhone() << std::endl;
      users.pop_front();
    }
  }
}

std::list<Meeting> FileManage::readMeetingsFromFile(void) {
  std::ifstream in("meeting.dat", std::ifstream::in);

  std::list<Meeting> meetings;  // create an empty list
  if (in) {
    // stores read data
    std::string sponsor, participator, stime, etime, title;

    if (!in.eof())
      in >> sponsor >> participator >> stime >> etime >> title;

    while (in && !in.eof()) {
      Meeting tmpMeeting(sponsor, participator, Date::stringToDate(stime),
                         Date::stringToDate(etime), title);
      meetings.push_back(tmpMeeting);

      in >> sponsor >> participator >> stime >> etime >> title;
    }
  }

  return meetings;
}

void FileManage::writeMeetingsToFile(std::list<Meeting> meetings) {
std::ofstream out("meeting.dat", std::ifstream::out);

  if (out) {
    while (!meetings.empty()) {
      out << std::setfill(' ') << std::setw(20)
          << meetings.front().getSponsor()
          << std::setw(20) << meetings.front().getParticipator()
          << std::setw(20)
          << Date::dateToString(meetings.front().getStartDate())
          << std::setw(20) << Date::dateToString(meetings.front().getEndDate())
          << std::setw(30) << meetings.front().getTitle() << std::endl;
      meetings.pop_front();
    }
  }
}
