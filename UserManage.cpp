#include "UserManage.h"

bool UserManage::instanceFlag_ = false;
UserManage* UserManage::instance_ = NULL;

UserManage::UserManage() : users_() {}

UserManage::~UserManage() {
  instance_ = NULL;
  instanceFlag_ = false;
}

UserManage* UserManage::getInstance(void) {
  if (!instanceFlag_) {
    instance_ = new UserManage();
    instanceFlag_ = true;
  }

  return instance_;
}

void UserManage::initUsersList(std::list<User> users) {
  users_ = users;
}

User* UserManage::findUserByName(std::string userName) {
  if (users_.empty())
    return NULL;

  for (typename std::list<User>::iterator it = users_.begin();
       it != users_.end(); ++it) {
    if (it->getName() == userName)
      return &(*it);
  }

  return NULL;
}

bool UserManage::createUser(std::string userName, std::string userPassword,
                            std::string userEmail, std::string userPhone) {
  if (findUserByName(userName) == NULL) {  // check if the user exists
    users_.push_back(User(userName, userPassword, userEmail, userPhone));
    return true;
  } else {
    return false;
  }
}

bool UserManage::deleteUser(User user) {
  if (users_.empty())
    return false;

  // search the user
  for (typename std::list<User>::iterator it = users_.begin();
       it != users_.end(); ++it) {
    if (it->getName() == user.getName()) {
      // delete the user
      users_.erase(it);
      return true;
    }
  }

  return false;
}

bool UserManage::updateUserPassword(User user, std::string newPassword) {
  User *found = findUserByName(user.getName());

  if (found != NULL) {
    found->setPassword(newPassword);
    return true;
  } else {
    return false;
  }
}

bool UserManage::updateUserEmail(User user, std::string newEmail) {
  User *found = findUserByName(user.getName());

  if (found != NULL) {
    found->setEmail(newEmail);
    return true;
  } else {
    return false;
  }
}

bool UserManage::updateUserPhone(User user, std::string newPhone) {
  User *found = findUserByName(user.getName());

  if (found != NULL) {
    found->setPhone(newPhone);
    return true;
  } else {
    return false;
  }
}

std::list<User> UserManage::listAllUsers(void) {
  return users_;
}
