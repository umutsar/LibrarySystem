#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

using namespace std;

class Admin : public User {
public:
    Admin(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive);
    void displayMenu() const override;
};

#endif