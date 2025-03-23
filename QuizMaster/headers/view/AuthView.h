#pragma once

#include <iostream>
#include <string>
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
};