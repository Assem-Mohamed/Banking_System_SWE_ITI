#ifndef CLIENT_H
#define CLIENT_H

#include "User.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Client : public User {
private:
    static int nextID;
    double balance = 0.0;
    string status = "active";
    vector<string> transactions;

public:
    Client() = default;

    Client(string uname, string pass, string ph, double bal = 0.0)
        : User(generateID(), uname, pass, ph), balance(bal) {}

    Client(string acc, string uname, string pass, string ph, double bal = 0.0)
        : User(acc, uname, pass, ph), balance(bal) {}

    bool isActive() const { return status == "active"; }

    void viewProfile() const override {
        cout << "\n--- Client Profile ---\n";
        cout << "AccID: " << AccID
             << "\nUsername: " << username
             << "\nBalance: " << balance
             << "\nStatus: " << status << endl;
    }


    bool transferOut(const string& targetAccID, double amount) {
        if (!isActive()) {
            cout << "Your account is disabled. Transfer denied.\n";
            return false;
        }

        if (amount <= 0) {
            cout << "Invalid amount! Must be greater than zero.\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;
        transactions.push_back("Transferred " + to_string(amount) + " to " + targetAccID);
        cout << "Transfer successful.\n";
        return true;
    }

    void addIncoming(const string& fromAccID, double amount) {
        balance += amount;
        transactions.push_back("Received " + to_string(amount) + " from " + fromAccID);
    }

    void viewTransactions() const {
        cout << "\n--- Transaction History ---\n";
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        for (const auto& t : transactions) cout << t << endl;
    }

    double getBalance() const { return balance; }
    void setStatus(const string& st) { status = st; }
    string getStatus() const { return status; }



private:
    static string generateID() {
        string id = "C" + string(3 - to_string(nextID).length(), '0') + to_string(nextID++);
        return id;
    }
};

int Client::nextID = 1;

#endif
