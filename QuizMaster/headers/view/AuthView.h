#pragma once

#include <iostream>
#include <string>
#include <conio.h> // For _getch()
#include "controller/AuthController.h"

class AuthView {
private:
    int choice = 0;
    AuthController authController;

public:
    AuthView() = default;

    void displayView();

private:
    void loginView();
    void registerView();
    void getPassword(std::string& password);
};