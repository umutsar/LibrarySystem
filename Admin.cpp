#include "Admin.h"
#include <iostream>

using namespace std;

Admin::Admin(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive)
    : User(id, userID, name, surname, password, isActive, true) {}

void Admin::displayMenu() const {
    cout << "Enter the action you want to take:\n";
    cout << "1- Borrow a book\n";
    cout << "2- Return book\n";
    cout << "3- Add book\n";
    cout << "4- Add user\n";
    cout << "0- Exit\n";
    cout << "Your choice: ";
}