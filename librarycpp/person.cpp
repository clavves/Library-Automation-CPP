#include "Person.hpp"

Person::Person(const string &name) : name(name) {}

Person::Person() : name("") {}

Person::~Person() {}

string Person::getName() const {
    return name;
}

void Person::setName(string newName) {
    name = newName;
}

void Person::displayInfo() const {
    cout << "Name: " << name << endl;
}