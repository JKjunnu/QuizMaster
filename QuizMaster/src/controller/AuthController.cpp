#include "controller/AuthController.h"
#include "view/AdminView.h"
#include "view/StudentView.h"

void AuthController::loginUser(std::string& username, std::string& password) {

    UserDetails userDetails = authService.authenticateUser(username, password);

    if (!userDetails.isAuthenticated) {
        std::cout << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << std::endl;
        std::cout << "Invalid credentials! Try again!" << std::endl;
        std::cout << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << std::endl;
        return;
    }

    if (userDetails.role == "admin") {
        AdminView adminView(userDetails);
        adminView.displayView();
    }

    if (userDetails.role == "student") {
        StudentView studentView(userDetails);
        studentView.displayView();

    }
    
    return;
}

void AuthController::registerUser(std::string& fullName, std::string& username, std::string& password, std::string& confirmPassword) {
    if (password != confirmPassword) {
        std::cout << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << std::endl;
        std::cout << "Passwords do not match. Please try again." << std::endl;
        std::cout << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << std::endl;
        return;
    }

    if (!authService.addUserToDB(fullName, username, password)) {
        std::cout << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << std::endl;
        std::cout << "Please Try again!"<<std::endl;
        std::cout << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout << std::endl;
    std::cout << "******************************" << std::endl;
    std::cout << std::endl;
    std::cout << "User created successfully" << std::endl;
    std::cout << std::endl;
    std::cout << "******************************" << std::endl;
    std::cout << std::endl;
    return;

}