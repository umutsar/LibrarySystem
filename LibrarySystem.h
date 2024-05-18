#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include "Database.h"
#include "User.h"

class LibrarySystem {
private:
    Database db;
    User *currentUser;

    void login();
    void logout();
    void borrowBook();
    void returnBook();
    void addBook();
    void addUser();

public:
    LibrarySystem();
    void run();
};

#endif