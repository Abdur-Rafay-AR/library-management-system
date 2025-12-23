#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

using namespace std;

struct Book {
    int bookID;
    string title;
    string author;
    int year;
    string category;
    bool isAvailable;

    Book() {}
    Book(int id, string t, string a, int y, string c) 
        : bookID(id), title(t), author(a), year(y), category(c), isAvailable(true) {}

    void print() const {
        cout << "ID: " << bookID << " | Title: " << title 
             << " | Author: " << author << " | Year: " << year 
             << " | Category: " << category 
             << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

#endif
