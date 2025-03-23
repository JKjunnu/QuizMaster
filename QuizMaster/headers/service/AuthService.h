#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>

#include "UserDetails.h"



class AuthService {

public:
    AuthService() = default;

    //register methods

    bool addUserToDB(const std::string& fullName, const std::string& username, const std::string& password);

    //login methods

    UserDetails authenticateUser(const std::string& username, const std::string& password);

    
};