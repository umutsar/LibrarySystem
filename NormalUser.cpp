#include "NormalUser.h"
#include <iostream>

using namespace std;

NormalUser::NormalUser(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive)
    : User(id, userID, name, surname, password, isActive, false) {}

void NormalUser::displayMenu() const {
    cout << "Enter the action you want to make:\n";
    cout << "1- Borrow a book\n";
    cout << "2- Return book\n";
    cout << "0- Exit\n";
    cout << "Your choice: ";
}