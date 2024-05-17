#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Book.h"

using namespace std;

class Magazine : public Book {
private:
    string issueNo;

public:
    Magazine(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable, const string &issueNo);
    void displayInfo() const override;
    string getIssueNo() const;
};

#endif
