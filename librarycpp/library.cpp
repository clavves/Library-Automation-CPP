#include "library.hpp"

using namespace std;

Library::Library(int bookCapacity, int memberCapacity, int adminCapacity)
    : bookCapacity(bookCapacity), memberCapacity(memberCapacity), adminCapacity(adminCapacity)

{
    books.reserve(bookCapacity);
    members.reserve(memberCapacity);
    admins = new Admin*[adminCapacity]; 
    adminCount = 0;
}

Library::~Library()
{
    for (Book *book : books)
    {
        delete book;
    }

    for (Member *member : members)
    {
        delete member;
    }

    for (int i = 0; i < adminCount; ++i)
    {
        delete admins[i];
    }

    delete[] admins;
}

void Library::addBook()
{
    if (books.size() >= bookCapacity)
    {
        cout << "The library is full." << endl;
        changeBookCapacity();
    }

    int bookID;
    string title, author, genreStr;
    int year;
    bool isBorrowed = 0;

    cout << "Enter Book ID: ";
    while (!(cin >> bookID) || cin.peek() != '\n')
    {
        cout << "Invalid input. Please enter a valid integer for Book ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (bookExists(bookID))
    {
        cout << "Book with the same ID already exists. Book not added." << endl;
        return;
    }

    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter Author: ";
    getline(cin, author);

    cout << "Enter Genre: ";
    getline(cin, genreStr);

    cout << "Enter Year: ";
    while (!(cin >> year) || cin.peek() != '\n')
    {
        cout << "Invalid input. Please enter a valid integer for Year: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Book *newBook = new Book(bookID, title, author, genreStr, year, isBorrowed);
    books.push_back(newBook);
    addBookToFile(*newBook);

    cout << "Book added to the library successfully." << endl;
}

void Library::changeBookCapacity()
{
    int answer;
    cout << "Would you like to change book capacity?" << endl;
    cout << "If yes, please write 1: ";
    cin >> answer;

    int increment;
    int newCapacity;
    vector<Book *> temp;

    switch (answer)
    {
    case 1:
        cout << "Enter the amount of incrementation: ";
        cin >> increment;

        newCapacity = increment + bookCapacity;

        temp.resize(newCapacity);

        for (int i = 0; i < books.size(); ++i)
        {
            temp[i] = books[i];
        }

        books = temp;
        bookCapacity = newCapacity;

        cout << "Capacity changed to " << bookCapacity << " books." << endl;
        break;

    default:
        cout << "Invalid choice." << endl;
        break;
    }
}

bool Library::bookExists(int bookID) const
{
    for (const Book *book : books)
    {
        if (book->getBookID() == bookID)
        {
            return true;
        }
    }
    return false;
}

void Library::deleteBook()
{
    int bookID;

    while (true)
    {
        cout << "Enter the Book ID to delete: ";
        while (!(cin >> bookID) || cin.peek() != '\n')
        {
            cout << "Invalid input. Please enter a valid integer for Book ID: ";
            cin.clear();
            while (cin.get() != '\n')
                continue;
        }

        int indexToDelete = -1;
        for (size_t i = 0; i < books.size(); ++i)
        {
            if (books[i]->getBookID() == bookID)
            {
                indexToDelete = static_cast<int>(i);
                break;
            }
        }

        if (indexToDelete != -1)
        {
            delete books[indexToDelete];
            books.erase(books.begin() + indexToDelete);
            deleteBookFromFile(bookID);

            cout << "Book with ID " << bookID << " deleted successfully." << endl;
            break;
        }
        else
        {
            cout << "Book with ID " << bookID << " not found. Please try again." << endl;
        }
    }
}

void Library::findBook()
{
    char answer;

    while (true)
    {
        int bookID;

        cout << "Enter the Book ID to find: ";
        while (!(cin >> bookID) || cin.peek() != '\n')
        {
            cout << "Invalid input. Please enter a valid integer for Book ID: ";
            cin.clear();
            while (cin.get() != '\n')
                continue;
        }

        bool bookFound = false;
        for (const Book *book : books)
        {
            if (book->getBookID() == bookID)
            {
                printBookDetails(*book);
                findBookInFile(bookID);
                bookFound = true;
                break;
            }
        }

        if (!bookFound)
        {
            cout << "Book with ID " << bookID << " not found." << endl;
        }

        cout << "Do you want to find another book? (y/n): ";
        cin >> answer;

        if (answer != 'y' && answer != 'Y')
        {
            break; 
        }
    }
}

void Library::updateBook()
{
    int bookID;
    bool found = false;

    while (!found)
    {
        cout << "Enter the Book ID to update: ";
        while (!(cin >> bookID) || cin.peek() != '\n')
        {
            cout << "Invalid input. Please enter a valid integer for Book ID: ";
            cin.clear();
            while (cin.get() != '\n')
                continue;
        }

        for (Book *book : books)
        {
            if (book->getBookID() == bookID)
            {
                found = true;

                cout << "Update Book Details for Book ID " << bookID << ":" << endl;

                cout << "What would you like to update?" << endl;
                cout << "1. Title" << endl;
                cout << "2. Author" << endl;
                cout << "3. Genre" << endl;
                cout << "4. Year" << endl;
                cout << "0. Exit" << endl;

                int choice;
                cout << "Enter the corresponding number: ";
                cin >> choice;

                while (choice != 0)
                {
                    switch (choice)
                    {
                    case 1:
                    {
                        cout << "Enter new title: ";
                        string newTitle;
                        cin.ignore();
                        getline(cin, newTitle);
                        if (!newTitle.empty())
                        {
                            book->setTitle(newTitle);
                        }
                        updateBookInFile(bookID,*book);
                        break;
                    }
                    case 2:
                    {
                        cout << "Enter new author: ";
                        string newAuthor;
                        cin.ignore();
                        getline(cin, newAuthor);
                        if (!newAuthor.empty())
                        {
                            book->setAuthor(newAuthor);
                        }
                        updateBookInFile(bookID,*book);
                        break;
                    }
                    case 3:
                    {
                        cout << "Enter new genre: ";
                        string newGenre;
                        cin.ignore();
                        getline(cin, newGenre);
                        if (!newGenre.empty())
                        {
                            book->setGenre(newGenre);
                        }
                        updateBookInFile(bookID,*book);
                        break;
                    }
                    case 4:
                    {
                        cout << "Enter new year: ";
                        int newYear;
                        while (!(cin >> newYear) || cin.peek() != '\n')
                        {
                            cout << "Invalid input. Please enter a valid integer for Year: ";
                            cin.clear();
                            while (cin.get() != '\n')
                                continue;
                        }
                        book->setYear(newYear);
                        updateBookInFile(bookID,*book);
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please enter a valid number." << endl;
                    }

                    cout << "Enter the corresponding number (0 to finish): ";
                    cin >> choice;
                }

                cout << "Book details updated successfully." << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Book with ID " << bookID << " not found. Do you want to try another Book ID? (y/n): ";
            char tryAgain;
            cin >> tryAgain;

            if (tryAgain != 'y' && tryAgain != 'Y')
            {
                break; 
            }
        }
    }
}

void Library::printBookDetails(const Book &book)
{
    cout << "Book Found." << endl;
    cout << "Book Details:" << endl;
    cout << "ID: " << book.getBookID() << endl;
    cout << "Title: " << book.getTitle() << endl;
    cout << "Author: " << book.getAuthor() << endl;
    cout << "Genre: " << book.getGenre() << endl;
    cout << "Year: " << book.getYear() << endl;
    cout << "Borrowed: " << (book.getIsBorrowed() ? "Yes" : "No") << endl;
}

void Library::displayBooks()
{
    if (books.empty())
    {
        cout << "No books available in the library." << endl;
        return;
    }

    cout << "List of Books in the Library:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "ID\tTitle\t\tAuthor\t\tGenre\t\tYear\tBorrowed" << endl;
    cout << "--------------------------------------" << endl;

    for (const Book *book : books)
    {
        cout << book->getBookID() << "\t"
             << book->getTitle() << "\t\t"
             << book->getAuthor() << "\t\t"
             << book->getGenre() << "\t\t"
             << book->getYear() << "\t"
             << (book->getIsBorrowed() ? "Yes" : "No") << endl;
    }

    cout << "--------------------------------------" << endl;
}

void Library::addMember()
{
    if (members.size() >= memberCapacity)
    {
        cout << "The library has reached its maximum member capacity." << endl;
        changeMemberCapacity();
    }

    int memberID;
    string memberName;

    cout << "Enter Member ID: ";
    while (!(cin >> memberID) || cin.peek() != '\n')
    {
        cout << "Invalid input. Please enter a valid integer for Member ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (memberExists(memberID))
    {
        cout << "Member with the same ID already exists. Member not added." << endl;
        return;
    }

    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, memberName);

    Member *newMember = new Member(memberName, memberID, 0);
    members.push_back(newMember);

    cout << "Member added to the library successfully." << endl;
}

void Library::changeMemberCapacity()
{
    int answer;
    cout << "Would you like to change member capacity?" << endl;
    cout << "If yes, please write 1: ";
    cin >> answer;

    int increment;
    int newCapacity;
    vector<Member *> temp;

    switch (answer)
    {
    case 1:
        cout << "Enter the amount of incrementation: ";
        cin >> increment;

        newCapacity = increment + memberCapacity;

        temp.resize(newCapacity);

        for (int i = 0; i < members.size(); ++i)
        {
            temp[i] = members[i];
        }

        members = temp;
        memberCapacity = newCapacity;

        cout << "Capacity changed to " << memberCapacity << " members." << endl;
        break;

    default:
        cout << "Invalid choice." << endl;
        break;
    }
}

bool Library::memberExists(int memberID) const
{
    for (const Member *member : members)
    {
        if (member->getMemberID() == memberID)
        {
            return true;
        }
    }
    return false;
}

void Library::deleteMember()
{
    int memberID;

    while (true)
    {
        cout << "Enter the Member ID to delete: ";
        while (!(cin >> memberID) || cin.peek() != '\n')
        {
            cout << "Invalid input. Please enter a valid integer for Member ID: ";
            cin.clear();
            while (cin.get() != '\n')
                continue;
        }

        int indexToDelete = -1;
        for (size_t i = 0; i < members.size(); ++i)
        {
            if (members[i]->getMemberID() == memberID)
            {
                indexToDelete = static_cast<int>(i);
                break;
            }
        }

        if (indexToDelete != -1)
        {
            for (Book *book : members[indexToDelete]->getBorrowedBooks())
            {
                book->setIsBorrowed(false);
            }

            delete members[indexToDelete];
            members.erase(members.begin() + indexToDelete);

            cout << "Member with ID " << memberID << " deleted successfully." << endl;
            break;
        }
        else
        {
            cout << "Member with ID " << memberID << " not found. Please try again." << endl;
        }
    }
}

void Library::findMember()
{
    char answer;

    while (true)
    {
        int memberID;

        cout << "Enter the Member ID to find: ";
        while (!(cin >> memberID) || cin.peek() != '\n')
        {
            cout << "Invalid input. Please enter a valid integer for Member ID: ";
            cin.clear();
            while (cin.get() != '\n')
                continue;
        }

        bool memberFound = false;
        for (const Member *member : members)
        {
            if (member->getMemberID() == memberID)
            {
                printMemberDetails(*member);
                memberFound = true;
                break;
            }
        }

        if (!memberFound)
        {
            cout << "Member with ID " << memberID << " not found." << endl;
        }

        cout << "Do you want to find another member? (y/n): ";
        cin >> answer;

        if (answer != 'y' && answer != 'Y')
        {
            break;
        }
    }
}

void Library::updateMember() {
    int memberID;
    bool found = false;

    while (!found) {
        cout << "Enter the Member ID to update: ";
        while (!(cin >> memberID) || cin.peek() != '\n') {
            cout << "Invalid input. Please enter a valid integer for Member ID: ";
            cin.clear();
            while (cin.get() != '\n')
                continue;
        }

        for (Member* member : members) {
            if (member->getMemberID() == memberID) {
                found = true;

                cout << "Update Member Details for Member ID " << memberID << ":" << endl;

                cout << "What would you like to update?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Borrowed Books" << endl;
                cout << "0. Exit" << endl;

                int choice;
                cout << "Enter the corresponding number: ";
                cin >> choice;

                while (choice != 0) {
                    switch (choice) {
                        case 1: {
                            cout << "Enter new name: ";
                            string newName;
                            cin.ignore();
                            getline(cin, newName);
                            if (!newName.empty()) {
                                member->setName(newName);
                                cout << "Name updated successfully." << endl;
                            }
                            break;
                        }
                        case 2: {
                            cout << "Do you want to update the borrowed books? (y/n): ";
                            char updateBooks;
                            cin >> updateBooks;

                            if (updateBooks == 'y' || updateBooks == 'Y') {
                                cout << "Borrowed Books:" << endl;
                                printBorrowedBooks(member->getBorrowedBooks());
                                updateBorrowedBooks(member);
                            }
                            break;
                        }
                        default:
                            cout << "Invalid choice. Please enter a valid number." << endl;
                    }

                    cout << "Enter the corresponding number (0 to finish): ";
                    cin >> choice;
                }

                cout << "Member details updated successfully." << endl;
                break;
            }
        }

        if (!found) {
            cout << "Member with ID " << memberID << " not found. Do you want to try another Member ID? (y/n): ";
            char tryAgain;
            cin >> tryAgain;

            if (tryAgain != 'y' && tryAgain != 'Y') {
                break;
            }
        }
    }
}

void Library::updateBorrowedBooks(Member* member) {
    int action;
    cout << "Choose action for updating borrowed books:" << endl;
    cout << "1. Borrow a book" << endl;
    cout << "2. Return a book" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter the corresponding number: ";
    cin >> action;

    switch (action) {
        case 1:
            borrowBook(member->memberID);
            break;
        case 2:
            returnBook();
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}

void Library::printMemberDetails(const Member &member)
{
    cout << "Member Found." << endl;
    cout << "Member Details:" << endl;
    cout << "ID: " << member.getMemberID() << endl;
    cout << "Name: " << member.getName() << endl;
    cout << "Borrowed Books Count: " << member.getBorrowedBookCount() << endl;

    if (member.getBorrowedBookCount() > 0)
    {
        cout << "Borrowed Books:" << endl;
        printBorrowedBooks(member.getBorrowedBooks());
    }
}

void Library::printBorrowedBooks(const vector<Book*>& borrowedBooks) {
    cout << "--------------------------------------" << endl;
    cout << "ID\tTitle" << endl;
    cout << "--------------------------------------" << endl;

    for (const Book* book : borrowedBooks) {
        cout << book->getBookID() << "\t" << book->getTitle() << endl;
    }

    cout << "--------------------------------------" << endl;
}

void Library::displayMembers()
{

    if (members.empty())
    {
        cout << "No members available in the library." << endl;
        return;
    }

    cout << "List of Members in the Library:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "ID\tName\t\tBorrowed Books Count" << endl;
    cout << "--------------------------------------" << endl;

    for (const Member *member : members)
    {
        cout << member->getMemberID() << "\t"
             << member->getName() << "\t\t"
             << member->getBorrowedBookCount() << endl;
    }

    cout << "--------------------------------------" << endl;
}

void Library::borrowBook(int memberID) {
    int bookID;


    Member* borrower = nullptr;
    for (Member* member : members) {
        if (member->getMemberID() == memberID) {
            borrower = member;
            break;
        }
    }

    if (!borrower) {
        cout << "Member with ID " << memberID << " not found." << endl;
        return;
    }

    cout << "Enter Book ID to borrow: ";
    while (!(cin >> bookID) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a valid integer for Book ID: ";
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }

    Book* bookToBorrow = nullptr;
    for (Book* book : books) {
        if (book->getBookID() == bookID) {
            bookToBorrow = book;
            break;
        }
    }

    if (!bookToBorrow) {
        cout << "Book with ID " << bookID << " not found." << endl;
        return;
    }

    if (bookToBorrow->getIsBorrowed()) {
        cout << "Book with ID " << bookID << " is already borrowed." << endl;
        return;
    }

    borrower->borrowBook(bookToBorrow);
    borrower->setBorrowedBookCount(borrower->getBorrowedBookCount() + 1);
    bookToBorrow->setIsBorrowed(true);

    cout << "Book with ID " << bookID << " borrowed successfully by Member with ID " << memberID << "." << endl;
}

void Library::returnBook() {
    int memberID, bookID;

    cout << "Enter Member ID: ";
    while (!(cin >> memberID) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a valid integer for Member ID: ";
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }

    Member* borrower = nullptr;
    for (Member* member : members) {
        if (member->getMemberID() == memberID) {
            borrower = member;
            break;
        }
    }

    if (!borrower) {
        cout << "Member with ID " << memberID << " not found." << endl;
        return;
    }

    cout << "Enter Book ID to return: ";
    while (!(cin >> bookID) || cin.peek() != '\n') {
        cout << "Invalid input. Please enter a valid integer for Book ID: ";
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }

    Book* bookToReturn = nullptr;
    for (Book* book : borrower->getBorrowedBooks()) {
        if (book->getBookID() == bookID) {
            bookToReturn = book;
            break;
        }
    }

    if (!bookToReturn) {
        cout << "Book with ID " << bookID << " not found in the borrowed books of Member with ID " << memberID << "." << endl;
        return;
    }

    borrower->returnBook(bookToReturn);
    borrower->setBorrowedBookCount(borrower->getBorrowedBookCount() - 1);
    bookToReturn->setIsBorrowed(false);

    cout << "Book with ID " << bookID << " returned successfully by Member with ID " << memberID << "." << endl;
}

Library& operator<<(Library& library, const Admin& admin) {
    if (library.adminCount < library.adminCapacity) {
        library.admins[library.adminCount++] = new Admin(admin);
        cout << "Admin added to the library successfully." << endl;
    } else {
        cout << "Admin capacity reached. Cannot add more admins." << endl;
    }

    return library;
}

void Library::addAdmin(Library& library) {
    string name, username, password;

    cout << "Enter Admin Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Admin Username: ";
    cin >> username;

    cout << "Enter Admin Password: ";
    cin >> password;

    Admin newAdmin(name, username, password);

    library << newAdmin;
}

void Library::displayAdmins()
{
    if (adminCount == 0)
    {
        cout << "No admins available in the library." << endl;
        return;
    }

    cout << "List of Admins in the Library:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Name\t\tUsername" << endl;
    cout << "--------------------------------------" << endl;

    for (int i = 0; i < adminCount; ++i)
    {
        cout << admins[i]->getName() << "\t\t" << admins[i]->getUsername() << endl;
    }

    cout << "--------------------------------------" << endl;
}

bool Library::adminLogin() {
    string enteredUsername, enteredPassword;

    cout << "Admin Login" << endl;
    cout << "Enter Username: ";
    cin >> enteredUsername;

    cout << "Enter Password: ";
    cin >> enteredPassword;

    for (int i = 0; i < adminCount; ++i) {
        if (admins[i]->getUsername() == enteredUsername && admins[i]->getPassword() == enteredPassword) {
            cout << "Login Successful. Welcome, " << admins[i]->getName() << "!" << endl;
            return true;
        }
    }

    cout << "Invalid Username or Password. Login Failed." << endl;
    return false;
}

ostream& Library::operator<<(ostream& output) const {
    int totalBorrowedBooks = 0;

    for (const Member* member : members) {
        totalBorrowedBooks += member->getBorrowedBookCount();
    }

    output << "Total Borrowed Books in the Library: " << totalBorrowedBooks << endl;

    return output;
}

int Library::getTotalBorrowedBooksCount() const {
    int totalBorrowedBooks = 0;

    for (const Member* member : members) {
        totalBorrowedBooks += member->getBorrowedBookCount();
    }

    return totalBorrowedBooks;
}

int Library::getTotalUnborrowedBooksCount() const {
    return books.size() - getTotalBorrowedBooksCount();
}

ifstream Library::openFileForReading(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return file;
}

ofstream Library::openFileForWriting(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    return file;
}

void Library::addBookToFile(const Book& newBook) {
    ofstream outFile("books.txt", ios::app);
    outFile << newBook.getBookID() << " " << newBook.getTitle() << " " << newBook.getAuthor() << " "
            << newBook.getGenre() << " " << newBook.getYear() << " " << newBook.getIsBorrowed() << endl;
}

void Library::deleteBookFromFile(int bookID) {
    vector<Book*> updatedBooks;
    ifstream inFile = openFileForReading("books.txt");

    int currentBookID;
    string title, author, genre;
    int year;
    bool isBorrowed;

    while (inFile >> currentBookID >> title >> author >> genre >> year >> isBorrowed) {
        if (currentBookID != bookID) {
            updatedBooks.push_back(new Book(currentBookID, title, author, genre, year, isBorrowed));
        }
    }

    inFile.close();

    ofstream outFile("books.txt", ios::trunc);
    for (const auto& book : updatedBooks) {
        outFile << book->getBookID() << " " << book->getTitle() << " " << book->getAuthor() << " "
                << book->getGenre() << " " << book->getYear() << " " << book->getIsBorrowed() << endl;
        delete book; 
    }
}

void Library::findBookInFile(int bookID) {
    ifstream inFile = openFileForReading("books.txt");

    int currentBookID;
    string title, author, genre;
    int year;
    bool isBorrowed;

    while (inFile >> currentBookID >> title >> author >> genre >> year >> isBorrowed) {
        if (currentBookID == bookID) {
            cout << "Book Found: " << title << " by " << author << endl;
            return;
        }
    }

    cout << "Book not found." << endl;

    inFile.close();
}

void Library::updateBookInFile(int bookID, const Book& updatedBook) {
    vector<Book*> updatedBooks;
    ifstream inFile = openFileForReading("books.txt");

    int currentBookID;
    string title, author, genre;
    int year;
    bool isBorrowed;

    while (inFile >> currentBookID >> title >> author >> genre >> year >> isBorrowed) {
        if (currentBookID == bookID) {
            updatedBooks.push_back(new Book(updatedBook));
        } else {
            updatedBooks.push_back(new Book(currentBookID, title, author, genre, year, isBorrowed));
        }
    }

    inFile.close();

    ofstream outFile("books.txt", ios::trunc);
    for (const auto& book : updatedBooks) {
        outFile << book->getBookID() << " " << book->getTitle() << " " << book->getAuthor() << " "
                << book->getGenre() << " " << book->getYear() << " " << book->getIsBorrowed() << endl;
        delete book; 
    }
}

void Library::open(Library& library) {
    while (true) {
        cout << "Opening Page" << endl;
        cout << "1. Sign In" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (adminLogin()) {
                    cout << "Login successful. Welcome to the Library!" << endl;
                    mainMenu(library);
                } else {
                    cout << "Login failed. Please try again or sign up." << endl;
                }
                break;
            }
            case 2: {
                addAdmin(library); 
                cout << "Sign up successful. Now you can sign in." << endl;
                break;
            }
            case 3:
                cout << "Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid number." << endl;
        }
    }
}

void Library::libraryMenu(Library &library) {
    while (true) {
        cout << "Library Menu" << endl;
        cout << "1. Borrowed Book Count" << endl;
        cout << "2. Unborrowed Book Count" << endl;
        cout << "3. Display Admins" << endl;
        cout << "4. Display Books" << endl;
        cout << "5. Display Members" << endl;
        cout << "6. Go Back" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Total Borrowed Books: " << library.getTotalBorrowedBooksCount() << endl;
                break;
            case 2:
                cout << "Total Unborrowed Books: " << library.getTotalUnborrowedBooksCount() << endl;
                break;
            case 3:
                library.displayAdmins();
                break;
            case 4:
                library.displayBooks();
                break;
            case 5:
                library.displayMembers();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Please enter a valid number." << endl;
        }
    }
}

void Library::bookMenu(Library &library) {
    while (true) {
        cout << "Book Menu" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Update Book" << endl;
        cout << "4. Find Book" << endl;
        cout << "5. Go Back" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.deleteBook();
                break;
            case 3:
                library.updateBook();
                break;
            case 4:
                library.findBook();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please enter a valid number." << endl;
        }
    }
}

void Library::memberMenu(Library &library) {
    while (true) {
        cout << "Member Menu" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Delete Member" << endl;
        cout << "3. Update Member" << endl;
        cout << "4. Find Member" << endl;
        cout << "5. Go Back" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addMember();
                break;
            case 2:
                library.deleteMember();
                break;
            case 3:
                library.updateMember();
                break;
            case 4:
                library.findMember();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please enter a valid number." << endl;
        }
    }
}

void Library::mainMenu(Library &library) {
    while (true) {
        cout << "Main Menu" << endl;
        cout << "1. Library" << endl;
        cout << "2. Book" << endl;
        cout << "3. Member" << endl;
        cout << "4. Logout" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                libraryMenu(library);
                break;
            case 2:
                bookMenu(library);
                break;
            case 3:
                memberMenu(library);
                break;
            case 4:
                cout << "Logged out. Goodbye!" << endl;
                exit(0); 
            default:
                cout << "Invalid choice. Please enter a valid number." << endl;
        }
    }
}

