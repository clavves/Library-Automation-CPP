#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.hpp"
#include "member.hpp"
#include "admin.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <cstdlib>

using namespace std;

class Member;
class Book;

class Library
{
    vector<Book *> books;
    int bookCapacity;
    vector<Member *> members;
    int memberCapacity;
    Admin** admins;
    int adminCount;
    int adminCapacity;

public:
    Library(int bookCapacity, int memberCapacity, int adminCapacity);
    ~Library();

    void addBook(); 
    void changeBookCapacity();
    bool bookExists(int bookID) const;
    void deleteBook();
    void findBook();
    void updateBook();
    void printBookDetails(const Book &book);
    void displayBooks();

    void addMember();
    void changeMemberCapacity();
    bool memberExists(int memberID) const;
    void deleteMember();
    void findMember();
    void updateMember();
    void updateBorrowedBooks(Member* member);
    void printMemberDetails(const Member &member);
    void printBorrowedBooks(const vector<Book*>& borrowedBooks);
    void displayMembers();
    void borrowBook(int memberID);
    void returnBook();


    friend Library& operator<<(Library& library, const Admin& admin);
    void addAdmin(Library& library);
    void displayAdmins();
    bool adminLogin();

    ostream& operator<<(ostream& output) const;
    int getTotalBorrowedBooksCount() const;
    int getTotalUnborrowedBooksCount() const;

    ifstream openFileForReading(const string& filename);
    ofstream openFileForWriting(const string& filename);
    void addBookToFile(const Book &newBook);
    void deleteBookFromFile(int bookID);
    void findBookInFile(int bookID);
    void updateBookInFile(int bookID, const Book &updatedBook);

    void open(Library &library);
    void libraryMenu(Library &library);
    void bookMenu(Library &library);
    void memberMenu(Library &library);
    void mainMenu(Library &library);

};

#endif