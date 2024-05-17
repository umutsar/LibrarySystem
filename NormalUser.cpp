#include "NormalUser.h"
#include <iostream>

using namespace std;

NormalUser::NormalUser(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive)
    : User(id, userID, name, surname, password, isActive, false) {}

void NormalUser::displayMenu() const {
    cout << "Yapmak istediginiz islemi girin:\n";
    cout << "1- Kitap ödünç al\n";
    cout << "2- Kitap iade et\n";
    cout << "0- Çıkış\n";
    cout << "Seçiminiz: ";
}
