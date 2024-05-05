#include "member.hpp"

Member::Member(const string &name, int memberID, int borrowedBookCount, const vector<Book *> &initialBorrowedBooks)
    : Person(name), memberID(memberID), borrowedBookCount(borrowedBookCount), borrowedBooks(initialBorrowedBooks) {
}

Member::Member() : memberID(0), borrowedBookCount(0) {
}

Member::~Member() {
}

int Member::getMemberID() const {
    return memberID;
}

int Member::getBorrowedBookCount() const {
    return borrowedBookCount;
}

const vector<Book*>& Member::getBorrowedBooks() const {
    return borrowedBooks;
}

void Member::setMemberID(int newMemberID) {
    memberID = newMemberID;
}

void Member::setBorrowedBookCount(int newBorrowedBookCount) {
    borrowedBookCount = newBorrowedBookCount;
}

void Member::setBorrowedBooks(const vector<Book *> &newBorrowedBooks) {
    borrowedBooks = newBorrowedBooks;
}

void Member::borrowBook(Book* book) {
    borrowedBooks.push_back(book);
}

void Member::returnBook(Book* book) {
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

void Member::displayInfo() const {
    Person::displayInfo();
    cout << "Member ID: " << memberID << endl;
    cout << "Borrowed Book Count: " << borrowedBookCount << endl;
}