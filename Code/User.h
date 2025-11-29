#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string AccID;
    string username;
    string password;
    string phoneNumber;

public:
    User() = default;

    User(string acc, string uname, string pass, string ph)
        : AccID(acc), username(uname), password(pass), phoneNumber(ph) {}

    virtual ~User() {}


    virtual void viewProfile() const = 0;

    bool login(const string& uname, const string& pass) const {
        return username == uname && password == pass;
    }

    string getUsername() const { return username; }
    string getPhone() const { return phoneNumber; }
    string getAccID() const { return AccID; }
};

#endif
