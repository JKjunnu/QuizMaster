#include "view/AuthView.h"
#include <limits>

void AuthView::displayView() {
    do {
        std::cout << "******************************" << std::endl;
        std::cout << "Welcome to Quiz Master!" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            loginView();
            break;
        case 2:
            registerView();
            break;
        case 3:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);
}

void AuthView::loginView() {
    std::string username;
    std::string password;
    std::cout << "******************************" << std::endl;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    authController.loginUser(username, password);
}

void AuthView::registerView() {
    std::string fullName;
    std::string username;
    std::string password;
    std::string confirmPassword;

    std::cout << "Enter full name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::getline(std::cin, fullName);

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    std::cout << "Confirm password: ";
    std::cin >> confirmPassword;

    authController.registerUser(fullName, username, password, confirmPassword);
}