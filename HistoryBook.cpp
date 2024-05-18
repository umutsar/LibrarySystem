#include "HistoryBook.h"
#include <iostream>

using namespace std;

HistoryBook::HistoryBook(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable, const string &historicalPeriod)
    : Book(id, title, author, isbn, publicationDate, isAvailable), historicalPeriod(historicalPeriod) {}

void HistoryBook::displayInfo() const {
    cout << "ID: " << id << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Publication Date: " << publicationDate << "\n"
              << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
              << "Historical Period: " << historicalPeriod << "\n";
}

string HistoryBook::getHistoricalPeriod() const {
    return historicalPeriod;
}