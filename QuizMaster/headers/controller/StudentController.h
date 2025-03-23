#pragma once

#include <string>
#include <iostream>
#include "service/StudentService.h"

class StudentController
{
private:
	UserDetails userDetails;
	StudentService studentService;

public:
	StudentController(UserDetails& userDetails);

	std::map<int, QuizDetails> getAllQuizzes();

	void saveScore(int& score, int& quizId);
};

