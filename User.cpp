#include "User.h"

using namespace std;

User::User(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive, bool isAdmin)
    : id(id), userID(userID), name(name), surname(surname), password(password), isActive(isActive), isAdmin(isAdmin) {}

int User::getId() const { return id; }
string User::getUserID() const { return userID; }
string User::getName() const { return name; }
string User::getSurname() const { return surname; }
bool User::getIsActive() const { return isActive; }
bool User::getIsAdmin() const { return isAdmin; }
string User::getPassword() const { return password; }
