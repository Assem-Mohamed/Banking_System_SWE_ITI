#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "Client.h"
#include <vector>
#include <string>
using namespace std;

class AccountManager
{

public:
    vector<Client*> clients;
    AccountManager() = default;

    AccountManager(const AccountManager& other)
    {
        for (auto c : other.clients)
        {
            clients.push_back(new Client(*c));
        }
    }

    AccountManager& operator=(const AccountManager& other)
    {
        if (this == &other) return *this;

        for (auto c : clients) delete c;
        clients.clear();

        for (auto c : other.clients)
        {
            clients.push_back(new Client(*c));
        }

        return *this;
    }


    ~AccountManager()
    {
        for (auto c : clients) delete c;
    }

    void registerClient(Client* c)
    {
        clients.push_back(c);
    }

    vector<Client*> getAllClients() const
    {
        return clients;
    }

    Client* findByAccID(const string& accID)
    {
        for (auto c : clients)
            if (c->getAccID() == accID)
                return c;
        return nullptr;
    }

    bool isUsernameTaken(const string& uname) const
    {
        for (auto c : clients)
            if (c->getUsername() == uname)
                return true;
        return false;
    }

    bool isPhoneTaken(const string& ph) const
    {
        for (auto c : clients)
            if (c->getPhone() == ph)
                return true;
        return false;
    }
};

#endif
