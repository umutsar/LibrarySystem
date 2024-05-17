#include "Magazine.h"
#include <iostream>

using namespace std;

Magazine::Magazine(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable, const string &issueNo)
    : Book(id, title, author, isbn, publicationDate, isAvailable), issueNo(issueNo) {}

void Magazine::displayInfo() const {
    cout << "ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Publication Date: " << publicationDate << "\n"
              << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
              << "Issue No: " << issueNo << "\n";
}

string Magazine::getIssueNo() const {
    return issueNo;
}
