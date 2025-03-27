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

bool AdminService::saveQuizName(int quizId, std::string quizName) {

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE quiz SET quiz_name=? WHERE quiz_id=?");
        pstmt->setString(1, quizName);
        pstmt->setInt(2, quizId);
        pstmt->execute();



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

bool AdminService::saveQuestionTitle(int questionId, std::string questionText) {

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE question SET question_text=? WHERE question_id=?");
        pstmt->setString(1, questionText);
        pstmt->setInt(2, questionId);
        pstmt->execute();



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

bool AdminService::saveOption(int questionId, int editOptionInput, std::string optionText) {


    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE question SET option"+std::to_string(editOptionInput)+"=? WHERE question_id=?");
        pstmt->setString(1, optionText);
        pstmt->setInt(2, questionId);
        pstmt->execute();



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

bool AdminService::saveCorrectOption(int questionId, int newCorrectOption) {

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE question SET correct_option=? WHERE question_id=?");
        pstmt->setInt(1, newCorrectOption);
        pstmt->setInt(2, questionId);
        pstmt->execute();



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

bool AdminService::deleteQuiz(int quizId) {

    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM score WHERE quiz_id=?");
        pstmt->setInt(1, quizId);
        pstmt->execute();

        pstmt = con->prepareStatement("DELETE FROM question WHERE quiz_id=?");
        pstmt->setInt(1, quizId);
        pstmt->execute();

        pstmt = con->prepareStatement("DELETE FROM quiz WHERE quiz_id=?");
        pstmt->setInt(1, quizId);
        pstmt->execute();



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