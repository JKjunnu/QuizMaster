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
};

