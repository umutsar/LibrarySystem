#ifndef NORMALUSER_H
#define NORMALUSER_H

#include "User.h"

using namespace std;

class NormalUser : public User {
public:
    NormalUser(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive);
    void displayMenu() const override;
};

#endif