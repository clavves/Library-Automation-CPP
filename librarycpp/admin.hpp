#ifndef ADMIN_H
#define ADMIN_H

#include "library.hpp"
#include "person.hpp"

class Library;

class Admin : public Person
{
protected:
    string username;
    string password;
    friend class Library;

public:
    Admin(string &name, string &username, string &password);
    Admin();
    virtual ~Admin() override {}

    string getUsername() const;
    string getPassword() const;

    void setUsername(string username);
    void setPassword(string password);

    virtual void displayInfo() const override;

    friend Library& operator<<(Library& library, const Admin& admin);


};

#endif