#pragma once
#include <string>
#include <vector>

struct QuestionDetails {
    int questionId;
    std::string questionText;
    std::vector<std::string> options; // Four options
    int correctOption; // (1-4)
    int userEnteredOption;
};