#pragma once
#include <string>
#include <vector>
#include "QuestionDetails.h"

struct QuizDetails {
    int quizId;
    std::string quizName;
    int numberOfQuestions;
    std::vector<QuestionDetails> questions;
};