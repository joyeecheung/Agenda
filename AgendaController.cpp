#include "AgendaController.h"
#include <iostream>
#include <iomanip>

AgendaController::AgendaController() : currentUser_(NULL), agendaService_() {
  startAgenda();
}

void AgendaController::getOperation() {
  std::cout << "-------------------------Agenda------------------------\n"
            << "Action : \n"
            << "l   - log in Agenda by user name and password\n"
            << "r   - register an Agenda account\n"
            << "q   - quit Agenda\n"
            << "-------------------------------------------------------\n"
            << "\nAgenda : ~$ ";

  std::string operation;
  std::cin >> operation;
  std::cout << '\n';

  while (executeOperation(operation)) {
    std::cout << "\n-------------------------Agenda------------------------\n"
              << "Action : \n"
              << "l   - log in Agenda by user name and password\n"
              << "r   - register an Agenda account\n"
              << "q   - quit Agenda\n"
              << "-------------------------------------------------------\n"
              << "\nAgenda : ~$ ";

    std::cin >> operation;
    std::cout << '\n';
  }

  quitAgenda();
}

void AgendaController::startAgenda() {
  agendaService_.startAgenda();
}

bool AgendaController::executeOperation(std::string op) {
  static const std::string actions[3] = {"l", "r", "q"};

  if (op == actions[2]) {
    return false;
  } else if (op == actions[1]) {
    userRegister();
    return true;
  } else if (op == actions[0]) {
    userLogIn();

    while (currentUser_ != NULL) {
      std::string nextop;
      enum opnumber {LogOut= 0, DeleteAccount, ListUsers, CreateMeeting,
                    ListMeeting, ListSMeeting, ListPMeeting, QueryMeeting,
                    QueryTime, DeleteMeeting, DeleteAll};
      static const std::string ops[] = {"o", "dc", "lu", "cm", "la",
                                               "las", "lap", "qm", "qt",
                                               "dm", "da"};

      std::cout << "\n-------------------------Agenda------------------------\n"
                << "Action : \n"
                << "o   - log out Agenda\n"
                << "dc  - delete Agenda account\n"
                << "lu  - list all Agenda user\n"
                << "cm  - create a meeting\n"
                << "la  - list all meetings\n"
                << "las - list all sponsor meetings\n"
                << "lap - list all participate meetings\n"
                << "qm  - query meeting by title\n"
                << "qt  - query meeting by time interval\n"
                << "dm  - delete meeting by title\n"
                << "da  - delete all meetings\n"
                << "-------------------------------------------------------\n"
                << "\nAgenda@" << currentUser_->getName() << " : # ";
      std::cin >> nextop;
      std::cout << '\n';

      if (nextop == ops[LogOut]) {
        userLogOut();
      } else if (nextop == ops[DeleteAccount]) {
        deleteUser();
      } else if (nextop == ops[ListUsers]) {
        listAllUsers();
      } else if (nextop == ops[CreateMeeting]) {
        createMeeting();
      } else if (nextop == ops[ListMeeting]) {
        listAllMeetings();
      } else if (nextop == ops[ListSMeeting]) {
        listAllSponsorMeetings();
      } else if (nextop == ops[ListPMeeting]) {
        listAllParticipateMeetings();
      } else if (nextop == ops[QueryMeeting]) {
        queryMeetingByTitle();
      } else if (nextop == ops[QueryTime]) {
        queryMeetingByTimeInterval();
      } else if (nextop == ops[DeleteMeeting]) {
        deleteMeetingByTitle();
      } else if (nextop == ops[DeleteAll]) {
        deleteAllMeetings();
      }
    }

    return true;
  } else {
    std::cout << "[error] undefined operation\n";
    return true;
  }
}

void AgendaController::userLogIn(void) {
  std::string userName, password;

  std::cout << "[log in] [user name] [password]\n";
  std::cout << "[log in] ";
  std::cin >> userName >> password;

  currentUser_ = agendaService_.userLogIn(userName, password);
  if (currentUser_ == NULL)
    std::cout << "[error] log in fail!\n";
  else
    std::cout << "[log in] succeed!\n";
}

void AgendaController::userRegister(void) {
  std::string userName, password, email, phone;
  std::cout << "[register] [user name] [password] [email] [phone]\n";
  std::cout << "[register] ";

  std::cin >> userName >> password >> email >> phone;

  if (agendaService_.userRegister(userName, password, email, phone))
    std::cout << "[register] succeed!\n";
  else
    std::cout << "[error] register fail!\n";
}

void AgendaController::quitAgenda(void) {
  agendaService_.quitAgenda();
}

void AgendaController::userLogOut(void) {
  currentUser_ = NULL;
}

void AgendaController::deleteUser(void) {
  if (agendaService_.deleteUser(*currentUser_)) {
    userLogOut();
    std::cout << "[delete Agenda account] succeed!\n";
  } else {
    std::cout << "[error] delete Agenda account fail!\n";
  }
}

void AgendaController::listAllUsers(void) {
  std::list<User> users = agendaService_.listAllUsers();

  std::cout << "[list all users]\n\n";
    std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
              << std::setw(8) << "name" << std::setw(16) << "email"
              << std::setw(11) << "phone" << '\n';
  for (typename std::list<User>::iterator it = users.begin();
       it != users.end(); ++it) {
    std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
              << std::setw(8) << it->getName() << std::setw(16)
              << it->getEmail()<< std::setw(11) << it->getPhone() << '\n';
  }
}

void AgendaController::createMeeting(void) {
  std::string title, participator, stime, etime;

  std::cout << "[create meeting] [title] [participator] "
            << "[start time(yyyy-mm-dd/hh:mm)] "
            << "[end time(yyyy-mm-dd/hh:mm)]\n"
            << "[create meeting] ";
  std::cin >> title >> participator >> stime >> etime;
  if (agendaService_.createMeeting(currentUser_->getName(), title,
      participator, stime, etime))
    std::cout << "[create meeting] succeed!\n";
  else
    std::cout << "[error] create meeting fail!\n";
}

void AgendaController::listAllMeetings(void) {
  std::cout << "[list all meetings]\n\n";
  printMeetings(agendaService_.listAllMeetings(currentUser_->getName()));
}

void AgendaController::listAllSponsorMeetings(void) {
  std::cout << "[list all sponsor meetings]\n\n";
  printMeetings(
      agendaService_.listAllSponsorMeetings(currentUser_->getName()));
}

void AgendaController::listAllParticipateMeetings(void) {
  std::cout << "[list all participate meetings]\n\n";
  printMeetings(
      agendaService_.listAllParticipateMeetings(currentUser_->getName()));
}

void AgendaController::queryMeetingByTitle(void) {
  std::string title;
  std::cout << "[query meeting] [title]:\n"
            << "[query meeting] ";
  std::cin >> title;

  std::cout << '\n' << std::setiosflags(std::ios::left) << std::setfill(' ')
    << std::setw(15) << "sponsor" << std::setw(15) << "participator"
    << std::setw(20) << "start time" << std::setw(20) << "end time" << '\n';

  Meeting *meeting = agendaService_.meetingQuery(title);

  if (meeting != NULL)
    std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
      << std::setw(15) << meeting->getSponsor()
      << std::setw(15) << meeting->getParticipator()
      << std::setw(20) << Date::dateToString(meeting->getStartDate())
      << std::setw(20) << Date::dateToString(meeting->getEndDate()) << '\n';
}

void AgendaController::queryMeetingByTimeInterval(void) {
  std::string stime, etime;
  std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)]"
            << " [end time(yyyy-mm-dd/hh:mm)]\n"
            << "[query meetings] ";
  std::cin >> stime >> etime;

  printMeetings(agendaService_.meetingQuery(currentUser_->getName(),
                                            stime, etime));
}

void AgendaController::deleteMeetingByTitle(void) {
  std::cout << "[delete meeting] [title]\n"
            << "[delete meeting] ";
  std::string title;
  std::cin >> title;
  if (agendaService_.deleteMeeting(currentUser_->getName(), title))
    std::cout << "[delete meeting by title] succeed!\n";
  else
    std::cout << "[error] delete meeting fail!\n";
}

void AgendaController::deleteAllMeetings(void) {
  if (agendaService_.deleteAllMeetings(currentUser_->getName()))
    std::cout << "[delete all meetings] succeed!\n";
  else
    std::cout << "[error] delete meetings fail!\n";
}

void AgendaController::printMeetings(std::list<Meeting> meetings) {
  std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
    << std::setw(15) << "title" << std::setw(15) << "sponsor"
    << std::setw(15) << "participator" << std::setw(20) << "start time"
    << std::setw(20) << "end time" << '\n';

  for (std::list<Meeting>::iterator it = meetings.begin();
       it != meetings.end(); ++it) {
    std::cout << std::setiosflags(std::ios::left) << std::setfill(' ')
      << std::setw(15) << it->getTitle() << std::setw(15) << it->getSponsor()
      << std::setw(15) << it->getParticipator()
              << std::setw(20) << Date::dateToString(it->getStartDate())
              << std::setw(20) << Date::dateToString(it->getEndDate()) << '\n';
  }
}
