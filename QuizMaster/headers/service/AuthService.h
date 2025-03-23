#pragma once

#include <string>
#include <vector>
#include <iostream>

struct authenticated {
    bool isAuthenticated;
    std::string role;
};

class AuthServiceClass {
private:
    std::vector<std::string> number{ "Jatin", "Krishna" };

public:
    AuthServiceClass() = default;

    //register methods

    bool addUserToDB(const std::string& fullName, const std::string& username, const std::string& password);

    //login methods

    authenticated authenticateUser(const std::string& username, const std::string& password);

    
};