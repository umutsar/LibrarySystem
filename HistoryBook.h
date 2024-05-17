#ifndef HISTORYBOOK_H
#define HISTORYBOOK_H

#include "Book.h"

using namespace std;

class HistoryBook : public Book {
private:
    string historicalPeriod;

public:
    HistoryBook(int id, const string &title, const string &author, const string &isbn, const string &publicationDate, bool isAvailable, const string &historicalPeriod);
    void displayInfo() const override;
    string getHistoricalPeriod() const;
};

#endif
