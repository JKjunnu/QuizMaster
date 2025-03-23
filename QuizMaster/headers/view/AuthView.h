#pragma once

#include <iostream>
#include <string>
#include "controller/AuthController.h"

class AuthViewClass {
private:
    int choice;
    AuthControllerClass authControllerClass;

public:
    AuthViewClass() = default;

    void authView();

private:
    void loginView();
    void registerView();
};