#pragma once

#include <string>
#include "service/AuthService.h"
#include <iostream>

class AuthController {
private:
    AuthService authService;

public:
    AuthController() = default;

    void loginUser(std::string& username, std::string& password);

    void registerUser(std::string& fullName, std::string& username, std::string& password, std::string& confirmPassword);

   
};