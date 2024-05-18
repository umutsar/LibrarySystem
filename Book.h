#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
protected:
    int id;
    string title;
    string author;
    string isbn;
    string publicationDate;
    bool isAvailable;

public:
    Book(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable);
    virtual ~Book() = default;

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    string getPublicationDate() const;
    bool getIsAvailable() const;

    virtual void displayInfo() const = 0;
};

#endif 