#include "Admin.h"
#include <iostream>

using namespace std;

Admin::Admin(int id, const string &userID, const string &name, const string &surname, const string &password, bool isActive)
    : User(id, userID, name, surname, password, isActive, true) {}

void Admin::displayMenu() const {
    cout << "Yapmak istediginiz islemi girin:\n";
    cout << "1- Kitap ödünç al\n";
    cout << "2- Kitap iade et\n";
    cout << "3- Kitap ekle\n";
    cout << "4- Kullanıcı ekle\n";
    cout << "0- Çıkış\n";
    cout << "Seçiminiz: ";
}
