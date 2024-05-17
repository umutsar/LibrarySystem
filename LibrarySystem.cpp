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
                    cout << "Geçersiz seçim, tekrar deneyin." << endl;
                    break;
            }
        }
    }
}

void LibrarySystem::login() {
    string userID, password;
    cout << "Kullanıcı ID: ";
    cin >> userID;
    cout << "Şifre: ";
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
        cout << "Geçersiz kullanıcı ID veya şifre, tekrar deneyin." << endl;
    }
}

void LibrarySystem::logout() {
    delete currentUser;
    currentUser = nullptr;
}

void LibrarySystem::borrowBook() {
    vector<Book*> books = db.getBooks();
    cout << "Mevcut kitaplar:\n";
    for (const auto& book : books) {
        book->displayInfo();
        cout << endl;
    }

    string isbn;
    cout << "Ödünç almak istediğiniz kitabın ISBN numarasını girin: ";
    cin >> isbn;

    for (auto book : books) {
        if (book->getISBN() == isbn) {
            if (book->getIsAvailable()) {
                string query = "UPDATE books SET isAvailable = 0 WHERE isbn = '" + isbn + "';";
                if (db.executeQuery(query)) {
                    cout << "Kitap başarıyla ödünç alındı.\n";
                } else {
                    cout << "Kitap ödünç alınırken bir hata oluştu.\n";
                }
            } else {
                cout << "Kitap şu anda ödünç alınmış durumda.\n";
            }
            return;
        }
    }
    cout << "Girilen ISBN numarasına ait kitap bulunamadı.\n";
}

void LibrarySystem::returnBook() {
    string isbn;
    cout << "İade etmek istediğiniz kitabın ISBN numarasını girin: ";
    cin >> isbn;

    vector<Book*> books = db.getBooks();
    for (auto book : books) {
        if (book->getISBN() == isbn) {
            if (!book->getIsAvailable()) {
                string query = "UPDATE books SET isAvailable = 1 WHERE isbn = '" + isbn + "';";
                if (db.executeQuery(query)) {
                    cout << "Kitap başarıyla iade edildi.\n";
                } else {
                    cout << "Kitap iade edilirken bir hata oluştu.\n";
                }
            } else {
                cout << "Kitap zaten iade edilmiş durumda.\n";
            }
            return;
        }
    }
    cout << "Girilen ISBN numarasına ait kitap bulunamadı.\n";
}

void LibrarySystem::addBook() {
    string type;
    cout << "Eklemek istediğiniz kitap türünü girin (Novel, Magazine, HistoryBook): ";
    cin >> type;

    string title, author, isbn, publicationDate, genre, issueNo, historicalPeriod;
    cout << "Başlık: ";
    cin.ignore();
    getline(cin, title);
    cout << "Yazar: ";
    getline(cin, author);
    cout << "ISBN: ";
    getline(cin, isbn);
    cout << "Yayın Tarihi: ";
    getline(cin, publicationDate);

    Book *newBook = nullptr;

    if (type == "Novel") {
        cout << "Tür (Genre): ";
        getline(cin, genre);
        newBook = new Novel(0, title, author, isbn, publicationDate, true, genre);
    } else if (type == "Magazine") {
        cout << "Sayı No (Issue No): ";
        getline(cin, issueNo);
        newBook = new Magazine(0, title, author, isbn, publicationDate, true, issueNo);
    } else if (type == "HistoryBook") {
        cout << "Tarihi Dönem (Historical Period): ";
        getline(cin, historicalPeriod);
        newBook = new HistoryBook(0, title, author, isbn, publicationDate, true, historicalPeriod);
    } else {
        cout << "Geçersiz kitap türü.\n";
        return;
    }

    if (db.addBook(*newBook)) {
        cout << "Kitap başarıyla eklendi.\n";
    } else {
        cout << "Kitap eklenirken bir hata oluştu.\n";
    }

    delete newBook;
}

void LibrarySystem::addUser() {
    string name, surname, password, userID;
    bool isAdmin;

    cout << "Kullanıcı ID: ";
    cin >> userID;
    cout << "İsim: ";
    cin.ignore();
    getline(cin, name);
    cout << "Soyisim: ";
    getline(cin, surname);
    cout << "Şifre: ";
    getline(cin, password);
    cout << "Admin mi? (1: Evet, 0: Hayır): ";
    cin >> isAdmin;

    User *newUser = nullptr;

    if (isAdmin) {
        newUser = new Admin(0, userID, name, surname, password, true);
    } else {
        newUser = new NormalUser(0, userID, name, surname, password, true);
    }

    if (db.addUser(*newUser)) {
        cout << "Kullanıcı başarıyla eklendi.\n";
    } else {
        cout << "Kullanıcı eklenirken bir hata oluştu.\n";
    }

    delete newUser;
}
