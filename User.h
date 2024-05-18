#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    int id;
    string userID;
    string name;
    string surname;
    string password;
    bool isActive;
    bool isAdmin;

public:
    User(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive, bool isAdmin);
    virtual ~User() = default;

    int getId() const;
    string getUserID() const;
    string getName() const;
    string getSurname() const;
    bool getIsActive() const;
    bool getIsAdmin() const;
    string getPassword() const;

    virtual void displayMenu() const = 0;
};

#endif