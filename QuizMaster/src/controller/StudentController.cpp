#include "controller/StudentController.h"

StudentController::StudentController(UserDetails& userDetails) : userDetails(userDetails), studentService(userDetails) {}

std::map<int, QuizDetails> StudentController::getAllQuizzes() {

	return studentService.getAllQuizzes();
}

void StudentController::saveScore(int& score, int& quizId) {
	studentService.saveScore(score, quizId);
}

std::vector<ScoreDetails> StudentController::quizHistory() {
	return studentService.quizHistory();
}