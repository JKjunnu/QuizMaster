#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>

#include "UserDetails.h"
#include "QuizDetails.h"

class AdminService
{
private:
	UserDetails userDetails;

public:
	AdminService(UserDetails& userDetails);

	bool saveQuiz(QuizDetails& quizDetails);

	bool saveQuizName(int quizId, std::string quizName);

	bool saveQuestionTitle(int questionId, std::string questionText);

	bool saveOption(int questionId, int editOptionInput, std::string optionText);

	bool saveCorrectOption(int questionId, int newCorrectOption);

	bool deleteQuiz(int quizId);
};

