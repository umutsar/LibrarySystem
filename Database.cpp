#include "Database.h"
#include "Admin.h"
#include "NormalUser.h"
#include "Novel.h"
#include "Magazine.h"
#include "HistoryBook.h"
#include <iostream>

using namespace std;

Database::Database(const string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::executeQuery(const string &query) {
    char *errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

vector<vector<string>> Database::fetchQueryResults(const string &query) {
    vector<vector<string>> results;
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return results;
    }

    int cols = sqlite3_column_count(stmt);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        vector<string> row;
        for (int col = 0; col < cols; col++) {
            const char *val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, col));
            row.push_back(val ? val : "");
        }
        results.push_back(row);
    }

    sqlite3_finalize(stmt);
    return results;
}

bool Database::addUser(const User &user) {
    string query = "INSERT INTO members (userID, name, surname, password, category, isActive, loginDate, isAdmin) VALUES ('" +
                        user.getUserID() + "', '" +
                        user.getName() + "', '" +
                        user.getSurname() + "', '" +
                        user.getPassword() + "', '" +
                        (user.getIsAdmin() ? "admin" : "normal") + "', " +
                        (user.getIsActive() ? "1" : "0") + ", " +
                        "datetime('now'), " +
                        (user.getIsAdmin() ? "1" : "0") + ");";
    return executeQuery(query);
}

bool Database::addBook(const Book &book) {
    string query = "INSERT INTO books (title, author, isbn, publicationDate, isAvailable, genre, issueNo, historicalPeriod) VALUES ('" +
                        book.getTitle() + "', '" +
                        book.getAuthor() + "', '" +
                        book.getISBN() + "', '" +
                        book.getPublicationDate() + "', " +
                        (book.getIsAvailable() ? "1" : "0") + ", " +
                        (dynamic_cast<const Novel*>(&book) ? "'" + dynamic_cast<const Novel*>(&book)->getGenre() + "'" : "NULL") + ", " +
                        (dynamic_cast<const Magazine*>(&book) ? "'" + dynamic_cast<const Magazine*>(&book)->getIssueNo() + "'" : "NULL") + ", " +
                        (dynamic_cast<const HistoryBook*>(&book) ? "'" + dynamic_cast<const HistoryBook*>(&book)->getHistoricalPeriod() + "'" : "NULL") + ");";
    return executeQuery(query);
}

vector<User*> Database::getUsers() {
    vector<User*> users;
    vector<vector<string>> results = fetchQueryResults("SELECT * FROM members");

    for (const auto &row : results) {
        if (row.size() == 9) {
            int id = stoi(row[0]);
            string userID = row[1];
            string name = row[2];
            string surname = row[3];
            string password = row[4];
            bool isActive = row[5] == "1";
            bool isAdmin = row[8] == "1";

            if (isAdmin) {
                users.push_back(new Admin(id, userID, name, surname, password, isActive));
            } else {
                users.push_back(new NormalUser(id, userID, name, surname, password, isActive));
            }
        }
    }

    return users;
}

vector<Book*> Database::getBooks() {
    vector<Book*> books;
    vector<vector<string>> results = fetchQueryResults("SELECT * FROM books");

    for (const auto &row : results) {
        if (row.size() == 9) {
            int id = stoi(row[0]);
            string title = row[1];
            string author = row[2];
            string isbn = row[3];
            string publicationDate = row[4];
            bool isAvailable = row[8] == "1";

            cout << "Fetched Book - ID: " << id << ", Title: " << title << ", Author: " << author << ", ISBN: " << isbn << ", Publication Date: " << publicationDate << ", isAvailable: " << isAvailable << endl;

            if (!row[5].empty()) {
                books.push_back(new Novel(id, title, author, isbn, publicationDate, isAvailable, row[5]));
            } else if (!row[6].empty()) {
                books.push_back(new Magazine(id, title, author, isbn, publicationDate, isAvailable, row[6]));
            } else if (!row[7].empty()) {
                books.push_back(new HistoryBook(id, title, author, isbn, publicationDate, isAvailable, row[7]));
            }
        }
    }

    return books;
}
