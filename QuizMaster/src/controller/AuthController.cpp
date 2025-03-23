#include "controller/AuthController.h"

void AuthControllerClass::loginUser(std::string& username, std::string& password) {

    authenticated details = authServiceClass.authenticateUser(username, password);

    if (!details.isAuthenticated) {
        std::cout << "Invalid credentials! Try again!" << std::endl;
        return;
    }

    if (details.role == "admin") {
        std::cout << "Hello admin!";
    }
    
    std::cout << "User is logged in!" << std::endl;
    return;
}

void AuthControllerClass::registerUser(std::string& fullName, std::string& username, std::string& password, std::string& confirmPassword) {
    if (password != confirmPassword) {
        std::cout << "Passwords do not match. Please try again." << std::endl;
        return;
    }

    if (!authServiceClass.addUserToDB(fullName, username, password)) {
        std::cout << "Please Try again!"<<std::endl;
        return;
    }

    std::cout << "User created successfully" << std::endl;
    return;

}