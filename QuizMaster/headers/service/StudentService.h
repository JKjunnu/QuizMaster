#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include <chrono>
#include <iomanip>
#include <ctime>

#include "UserDetails.h"
#include "QuizDetails.h"
#include "ScoreDetails.h"


class StudentService
{
private:
	UserDetails userDetails;

public: 
	StudentService(UserDetails& userDetails);

	std::map<int, QuizDetails> getAllQuizzes();

	void saveScore(int& score , int& quizId);

	std::vector<ScoreDetails> quizHistory();
};

