#ifndef BOOK_HPP
#define BOOK_HPP

#include "library.hpp"
#include <vector>

using namespace std;


class Book
{
protected:
    int bookID;
    string title;
    string author;
    string genre;
    int year;
    bool isBorrowed;

public:
    Book(int bookID, string &title, string &author, string &genre, int year, bool isBorrowed);
    Book();

    int getBookID() const;
    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    int getYear() const;
    bool getIsBorrowed() const;

    void setBookID(int bookID);
    void setTitle(string title);
    void setAuthor(string author);
    void setGenre(string genre);
    void setYear(int year);
    void setIsBorrowed(bool isBorrowed);

};

#endif