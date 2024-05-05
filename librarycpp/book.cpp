#include "book.hpp"

Book::Book(int bookID, string &title, string &author, string &genre, int year, bool isBorrowed)
    : bookID(bookID), title(title), author(author), genre(genre), year(year), isBorrowed(isBorrowed) {}

Book::Book() : bookID(0), title(""), author(""), genre(""), year(0), isBorrowed(false) {}



int Book::getBookID() const {
    return bookID;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getGenre() const {
    return genre;
}

int Book::getYear() const {
    return year;
}

bool Book::getIsBorrowed() const {
    return isBorrowed;
}

void Book::setBookID(int newBookID) {
    bookID = newBookID;
}




void Book::setTitle(string newTitle) {
    title = newTitle;
}

void Book::setAuthor(string newAuthor) {
    author = newAuthor;
}

void Book::setGenre(string newGenre) {
    genre = newGenre;
}

void Book::setYear(int newYear) {
    year = newYear;
}

void Book::setIsBorrowed(bool newIsBorrowed) {
    isBorrowed = newIsBorrowed;
}