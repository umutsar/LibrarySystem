#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include "User.h"
#include "Book.h"

using namespace std;

class Database {
private:
    sqlite3 *db;

public:
    Database(const string &dbPath);
    ~Database();

    bool executeQuery(const string &query);
    vector<vector<string>> fetchQueryResults(const string &query);

    bool addUser(const User &user);
    bool addBook(const Book &book);
    vector<User*> getUsers();
    vector<Book*> getBooks();
};

#endif