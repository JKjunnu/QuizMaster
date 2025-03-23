#include "service/StudentService.h"

import DBConn;

StudentService::StudentService(UserDetails& userDetails) : userDetails(userDetails) {}

std::map<int, QuizDetails> StudentService::getAllQuizzes() {

    std::map<int, QuizDetails> quizMap;

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM quiz NATURAL JOIN question");
        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next()) {

            int quizId = res->getInt("quiz_id");

            if (!quizMap.contains(quizId)) {
                QuizDetails quiz;
                quiz.quizId = quizId;
                quiz.quizName = res->getString("quiz_name");
                quiz.numberOfQuestions = res->getInt("no_of_questions");
                std::vector<QuestionDetails> questions;
                quiz.questions = questions;
                quizMap[quizId] = quiz;
            }

            QuestionDetails question;

            question.questionId = res->getInt("question_id");
            question.questionText = res->getString("question_text");

            std::vector<std::string> options;
            
            options.push_back(res->getString("option1"));
            options.push_back(res->getString("option2"));
            options.push_back(res->getString("option3"));
            options.push_back(res->getString("option4"));

            question.options = options;

            question.correctOption = res->getInt("correct_option");

            quizMap[quizId].questions.push_back(question);
            
        }

        delete res;
        delete pstmt;
        delete con;

        return quizMap;


        

    }
    catch (sql::SQLException e) {
        std::cout << "******************************" << std::endl;
        std::cout << "Could not execute query: " << e.what() << std::endl;
        std::cout << "******************************" << std::endl;
        return quizMap;

    }
}

void StudentService::saveScore(int& score, int&quizId) {

    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time;

    // Use localtime_s for safer conversion
    localtime_s(&local_time, &now_time);

    // Format the current date and time
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    std::string datetime_str = oss.str();

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO score(user_id, quiz_id, total_scored, time_stamp) VALUES(?,?,?,?)");
        pstmt->setInt(1, userDetails.userId);
        pstmt->setInt(2, quizId);
        pstmt->setInt(3, score);
        pstmt->setDateTime(4, datetime_str);

        pstmt->execute();

        delete pstmt;
        delete con;

        return;
    }
    catch (sql::SQLException e) {
        std::cout << "******************************" << std::endl;
        std::cout << "Could not execute query: " << e.what() << std::endl;
        std::cout << "******************************" << std::endl;
        return;

    }

}
