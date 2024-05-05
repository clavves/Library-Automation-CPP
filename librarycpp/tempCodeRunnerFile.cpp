#include <iostream>
#include <string>

#include "library.cpp"
#include "book.cpp"
#include "person.cpp"
#include "member.cpp"
#include "admin.cpp"

int main()
{
    Library library(5,5,5);

    addAdmin(library);
    library.displayAdmins();
    library.addBook();
    /*library.findBook();
    library.updateBook();
    library.deleteBook();
    library.displayBooks();*/

    library.addMember();
    //library.findMember();
    library.updateMember();
    //library.deleteMember();
    library.displayMembers();
}