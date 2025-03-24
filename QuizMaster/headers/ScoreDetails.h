#pragma once

#include <string>

struct ScoreDetails {
    int scoreId;
    int quizId;
    std::string quizName;
    int noOfQuestions;
    std::string timeStamp;
    int totalScored;
};