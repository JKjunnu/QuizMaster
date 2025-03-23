#include "controller/AdminController.h"

AdminController::AdminController(UserDetails& userDetails) : userDetails(userDetails), adminService(userDetails){}

void AdminController::saveQuiz(QuizDetails& quizDetails) {
	if (!adminService.saveQuiz(quizDetails)) {
		std::cout << "******************************" << std::endl;
		std::cout << "Error creating quiz!" << std::endl;
		std::cout << "******************************" << std::endl;
		return;
	}

	std::cout << "******************************" << std::endl;
	std::cout << "Quiz created successfully!" << std::endl;
	std::cout << "******************************" << std::endl;
	return;
}