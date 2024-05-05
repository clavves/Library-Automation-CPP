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

    const char name[] = "y";
    const char username[] = "yy";
    const char password[] = "yyy";

    string nameStr(name);
    string usernameStr(username);
    string passwordStr(password);

    Admin admin(nameStr, usernameStr, passwordStr);
    library<<admin;

    library.open(library);
}
