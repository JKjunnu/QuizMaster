#pragma once

#include <string>
#include "service/AuthService.h"
#include <iostream>

class AuthControllerClass {
private:
    AuthServiceClass authServiceClass;

public:
    AuthControllerClass() = default;

    void loginUser(std::string& username, std::string& password);

    void registerUser(std::string& fullName, std::string& username, std::string& password, std::string& confirmPassword);

   
};