#pragma once
#include <string>

struct UserDetails {
    bool isAuthenticated;
    std::string fullName;
    std::string username;
    int userId;
    std::string role;
};