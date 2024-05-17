#include "Book.h"

using namespace std;

Book::Book(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable)
    : id(id), title(title), author(author), isbn(isbn), publicationDate(publicationDate), isAvailable(isAvailable) {}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
string Book::getPublicationDate() const { return publicationDate; }
bool Book::getIsAvailable() const { return isAvailable; }
