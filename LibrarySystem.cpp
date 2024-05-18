#include "LibrarySystem.h"
#include "Admin.h"
#include "NormalUser.h"
#include "Novel.h"
#include "Magazine.h"
#include "HistoryBook.h"
#include <iostream>

using namespace std;

LibrarySystem::LibrarySystem() : db("library.db"), currentUser(nullptr) {}

void LibrarySystem::run() {
    while (true) {
        if (!currentUser) {
            login();
        } else {
            currentUser->displayMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    borrowBook();
                    break;
                case 2:
                    returnBook();
                    break;
                case 3:
                    if (currentUser->getIsAdmin()) {
                        addBook();
                    }
                    break;
                case 4:
                    if (currentUser->getIsAdmin()) {
                        addUser();
                    }
                    break;
                case 0:
                    logout();
                    break;
                default:
                    cout << "Invalid selection, try again." << endl;
                    break;
            }
        }
    }
}

void LibrarySystem::login() {
    string userID, password;
    cout << "User ID: ";
    cin >> userID;
    cout << "Password: ";
    cin >> password;

    vector<User*> users = db.getUsers();
    for (auto user : users) {
        if (user->getUserID() == userID && user->getPassword() == password) {
            currentUser = user;
            cout << "Login successful for user: " << user->getName() << endl;
            break;
        }
    }

    if (!currentUser) {
        cout << "Invalid user ID or password, try again." << endl;
    }
}

void LibrarySystem::logout() {
    delete currentUser;
    currentUser = nullptr;
}

void LibrarySystem::borrowBook() {
    vector<Book*> books = db.getBooks();
    cout << "Available books:\n";
    for (const auto& book : books) {
        book->displayInfo();
        cout << endl;
    }

    string isbn;
    cout << "Enter the ISBN number of the book you want to borrow: ";
    cin >> isbn;

    for (auto book : books) {
        if (book->getISBN() == isbn) {
            if (book->getIsAvailable()) {
                string query = "UPDATE books SET isAvailable = 0 WHERE isbn = '" + isbn + "';";
                if (db.executeQuery(query)) {
                    cout << "The book has been borrowed successfully.\n";
                } else {
                    cout << "An error occurred while borrowing the book.\n";
                }
            } else {
                cout << "The book is currently on loan.\n";
            }
            return;
        }
    }
    cout << "The book with the entered ISBN number was not found.\n";
}

void LibrarySystem::returnBook() {
    string isbn;
    cout << "Enter the ISBN number of the book you want to return: ";
    cin >> isbn;

    vector<Book*> books = db.getBooks();
    for (auto book : books) {
        if (book->getISBN() == isbn) {
            if (!book->getIsAvailable()) {
                string query = "UPDATE books SET isAvailable = 1 WHERE isbn = '" + isbn + "';";
                if (db.executeQuery(query)) {
                    cout << "The book was returned successfully.\n";
                } else {
                    cout << "An error occurred while returning the book.\n";
                }
            } else {
                cout << "The book has already been returned.\n";
            }
            return;
        }
    }
    cout << "The book with the entered ISBN number was not found.\n";
}

void LibrarySystem::addBook() {
    string type;
    cout << "Enter the type of book you want to add (Novel, Magazine, HistoryBook): ";
    cin >> type;

    string title, author, isbn, publicationDate, genre, issueNo, historicalPeriod;
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Writer: ";
    getline(cin, author);
    cout << "ISBN: ";
    getline(cin, isbn);
    cout << "Release date: ";
    getline(cin, publicationDate);

    Book *newBook = nullptr;

    if (type == "Novel") {
        cout << "Genre: ";
        getline(cin, genre);
        newBook = new Novel(0, title, author, isbn, publicationDate, true, genre);
    } else if (type == "Magazine") {
        cout << "Issue No: ";
        getline(cin, issueNo);
        newBook = new Magazine(0, title, author, isbn, publicationDate, true, issueNo);
    } else if (type == "HistoryBook") {
        cout << "Historical Period: ";
        getline(cin, historicalPeriod);
        newBook = new HistoryBook(0, title, author, isbn, publicationDate, true, historicalPeriod);
    } else {
        cout << "Invalid book type.\n";
        return;
    }

    if (db.addBook(*newBook)) {
        cout << "The book has been added successfully.\n";
    } else {
        cout << "An error occurred while adding the book.\n";
    }

    delete newBook;
}

void LibrarySystem::addUser() {
    string name, surname, password, userID;
    bool isAdmin;

    cout << "User ID: ";
    cin >> userID;
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Surname: ";
    getline(cin, surname);
    cout << "Password: ";
    getline(cin, password);
    cout << "Admin ? (1: Yes, 0: No): ";
    cin >> isAdmin;

    User *newUser = nullptr;

    if (isAdmin) {
        newUser = new Admin(0, userID, name, surname, password, true);
    } else {
        newUser = new NormalUser(0, userID, name, surname, password, true);
    }

    if (db.addUser(*newUser)) {
        cout << "User added successfully.\n";
    } else {
        cout << "An error occurred while adding the user.\n";
    }

    delete newUser;
}