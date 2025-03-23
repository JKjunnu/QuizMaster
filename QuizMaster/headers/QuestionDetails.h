#pragma once
#include <string>
#include <vector>

struct QuestionDetails {
    std::string questionText;
    std::vector<std::string> options; // Four options
    int correctOption; // (1-4)
};