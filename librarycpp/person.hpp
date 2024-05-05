#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;

public:
    Person(const string &name);
    Person();
    virtual ~Person();

    string getName() const;

    void setName(string name);

    virtual void displayInfo() const;
};

#endif