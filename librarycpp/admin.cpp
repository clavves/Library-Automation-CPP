#include "Admin.hpp"

Admin::Admin(string &name, string &username, string &password)
    : Person(name), username(username), password(password) {
}

Admin::Admin() : username(""), password("") {
}

string Admin::getUsername() const {
    return username;
}

string Admin::getPassword() const {
    return password;
}

void Admin::setUsername(string newUsername) {
    username = newUsername;
}

void Admin::setPassword(string newPassword) {
    password = newPassword;
}

void Admin::displayInfo() const {
    Person::displayInfo();
    cout << "Username: " << username << endl;
}