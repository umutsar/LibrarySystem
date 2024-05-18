#include "Novel.h"
#include <iostream>

using namespace std;

Novel::Novel(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable, const string &genre)
    : Book(id, title, author, isbn, publicationDate, isAvailable), genre(genre) {}

void Novel::displayInfo() const {
    cout << "ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Publication Date: " << publicationDate << "\n"
              << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
              << "Genre: " << genre << "\n";
}

string Novel::getGenre() const {
    return genre;
}