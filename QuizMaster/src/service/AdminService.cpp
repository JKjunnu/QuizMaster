#include "service/AdminService.h"

import DBConn;

AdminService::AdminService(UserDetails& userDetails) : userDetails(userDetails) {}

bool AdminService::saveQuiz(QuizDetails& quizDetails) {

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO quiz(quiz_name, no_of_questions) VALUES(?,?)");
        pstmt->setString(1, quizDetails.quizName);
        pstmt->setInt(2, quizDetails.numberOfQuestions);
        pstmt->execute();
        

        pstmt = con->prepareStatement("SELECT quiz_id FROM quiz WHERE quiz_name=?");
        pstmt->setString(1, quizDetails.quizName);

        sql::ResultSet* res = pstmt->executeQuery();
        int quizId;
        if (res->next()) {
          
            quizId = res->getInt("quiz_id");
            delete res;
        }
        else {
            std::cout << "Error: Quiz ID Not Found!";
            delete res;
            delete pstmt;
            delete con;
            return false;
        }

        pstmt = con->prepareStatement("INSERT INTO question(quiz_id, question_text, option1, option2, option3, option4, correct_option) VALUES(?,?,?,?,?,?,?)");

        for (QuestionDetails question : quizDetails.questions) {
            
            pstmt->setInt(1, quizId);
            pstmt->setString(2, question.questionText);
            int i = 3;
            for (std::string option : question.options) {
                pstmt->setString(i, option);
                i++;
            }
            pstmt->setInt(7, question.correctOption);
            pstmt->execute();
            
        }

        
        delete pstmt;
        delete con;
        return true;

    }
    catch (sql::SQLException e) {
        std::cout << "******************************" << std::endl;
        std::cout << "Could not execute query: " << e.what() << std::endl;
        std::cout << "******************************" << std::endl;
        return false;

    }

}