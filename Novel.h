#ifndef NOVEL_H
#define NOVEL_H

#include "Book.h"

using namespace std;

class Novel : public Book {
private:
    string genre;

public:
    Novel(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable, const string &genre);
    void displayInfo() const override;
    string getGenre() const;
};

#endif