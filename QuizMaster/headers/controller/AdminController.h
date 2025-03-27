#pragma once

#include <string>
#include <iostream>
#include "service/AdminService.h"
#include "service/StudentService.h"



class AdminController
{

private:
	UserDetails userDetails;
	AdminService adminService;
	StudentService studentService;

public:
	AdminController(UserDetails& userDetails);

	void saveQuiz(QuizDetails& quizDetails);

	std::map<int, QuizDetails> getAllQuizzes();

	void saveQuizName(int quizId, std::string quizName);

	void saveQuestionTitle(int questionId, std::string questionText);

	void saveOption(int questionId, int editOptionInput, std::string optionText);

	void saveCorrectOption(int questionId, int newCorrectOption);

	void deleteQuiz(int quizId);
};

