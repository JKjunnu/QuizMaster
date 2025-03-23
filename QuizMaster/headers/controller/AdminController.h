#pragma once

#include <string>
#include <iostream>
#include "service/AdminService.h"



class AdminController
{

private:
	UserDetails userDetails;
	AdminService adminService;

public:
	AdminController(UserDetails& userDetails);

	void saveQuiz(QuizDetails& quizDetails);


};

