#pragma once

#include <iostream>
#include <string>
#include "controller/StudentController.h"

class StudentView
{
private:
	int choice = 0;
	UserDetails userDetails;
	StudentController studentController;

public:
	StudentView(UserDetails& userDetails);

	void displayView();

	void attemptQuiz();

	void quizHistory();
};

