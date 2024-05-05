#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "library.hpp"
#include "person.hpp"
#include <vector>
#include <algorithm>

using namespace std;

class Member : public Person
{
    int memberID;
    vector<Book *> borrowedBooks;
    int borrowedBookCount;

    friend class Library;

public:
    Member(const string &name, int memberID, int borrowedBookCount, const vector<Book *> &initialBorrowedBooks = {});
    Member();
    virtual ~Member() override;


    int getMemberID() const;
    int getBorrowedBookCount() const;
    const vector<Book*>& getBorrowedBooks() const;

    void setMemberID(int newMemberID);
    void setBorrowedBookCount(int newBorrowedBookCount);
    void setBorrowedBooks(const vector<Book *> &newBorrowedBooks);

    void borrowBook(Book* book);
    void returnBook(Book* book);

    virtual void displayInfo() const override;
};

#endif