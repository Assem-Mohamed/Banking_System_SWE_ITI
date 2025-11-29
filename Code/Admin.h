#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "AccountManager.h"
#include <iostream>
using namespace std;

class Admin : public User {
private:
    AccountManager* accountMgr;
    static int nextAdminID;

    static string generateAdminID() {
        string id = "A" + string(3 - to_string(nextAdminID).length(), '0') + to_string(nextAdminID++);
        return id;
    }

public:

    Admin(string acc, string uname, string pass, string ph, AccountManager* mgr)
        : User(acc == "" ? generateAdminID() : acc, uname, pass, ph),
          accountMgr(mgr) {}

    void viewProfile() const override {
        cout << "\n--- Admin Profile ---\n";
        cout << "AccID: " << AccID
             << "\nUsername: " << username
             << "\nPhone: " << phoneNumber << endl;
    }

    void viewClients() {
        cout << "\n--- All Clients ---\n";
        for (auto c : accountMgr->getAllClients()) {
            c->viewProfile();
            cout << "-----------------\n";
        }
    }

    Client* searchClient(const string& accID) {
        return accountMgr->findByAccID(accID);
    }

    void enableAccount(const string& accID) {
        Client* c = accountMgr->findByAccID(accID);
        if (!c) cout << "Client not found.\n";
        else {
            c->setStatus("active");
            cout << "Account enabled.\n";
        }
    }

    void disableAccount(const string& accID) {
        Client* c = accountMgr->findByAccID(accID);
        if (!c) cout << "Client not found.\n";
        else {
            c->setStatus("disabled");
            cout << "Account disabled.\n";
        }
    }

    void viewStatistics() {
        int total = accountMgr->getAllClients().size();
        int active = 0, disabled = 0;

        for (auto c : accountMgr->getAllClients()) {
            if (c->getStatus() == "active") active++;
            else disabled++;
        }

        cout << "\n--- Statistics ---\n";
        cout << "Total clients: " << total
             << "\nActive: " << active
             << "\nDisabled: " << disabled << endl;
    }

    AccountManager* getManager() { return accountMgr; }
};

int Admin::nextAdminID = 1;

#endif
