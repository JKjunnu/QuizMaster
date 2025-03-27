#include "controller/AdminController.h"

AdminController::AdminController(UserDetails& userDetails) : userDetails(userDetails), adminService(userDetails), studentService(userDetails){}

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

std::map<int, QuizDetails> AdminController::getAllQuizzes() {
	return studentService.getAllQuizzes();
}

void AdminController::saveQuizName(int quizId, std::string quizName) {
	if (!adminService.saveQuizName(quizId, quizName)) {
		std::cout << "Could not save Quiz Name!" << std::endl;
	}
	return;
}

void AdminController::saveQuestionTitle(int questionId, std::string questionText) {
	if (!adminService.saveQuestionTitle(questionId, questionText)) {
		std::cout << "Could not save Question Text!" << std::endl;
	}
	return;
}

void AdminController::saveOption(int questionId, int editOptionInput, std::string optionText) {

	if (!adminService.saveOption(questionId, editOptionInput, optionText)) {
		std::cout << "Could not save Option!" << std::endl;
	}
	return;
}

void AdminController::saveCorrectOption(int questionId, int newCorrectOption) {

	if (!adminService.saveCorrectOption(questionId, newCorrectOption)) {
		std::cout << "Could not save Correct Option!" << std::endl;
	}
	return;
}

void AdminController::deleteQuiz(int quizId) {
	if (!adminService.deleteQuiz(quizId)) {
		std::cout << "Could not delete Quiz!" << std::endl;
	}
	return;
}