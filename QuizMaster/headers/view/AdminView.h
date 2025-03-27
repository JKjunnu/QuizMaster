#pragma once

#include <iostream>
#include <string>
#include "controller/AdminController.h"

class AdminView
{

private:
	int choice = 0;
	UserDetails userDetails;
	AdminController adminController;

public:
	AdminView(UserDetails& userDetails);

	void displayView();

	void createQuiz();

	void editQuiz();

	void deleteQuiz();

};

