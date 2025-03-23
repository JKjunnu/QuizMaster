#include "view/StudentView.h"

#include <limits>

StudentView::StudentView(UserDetails& userDetails) : userDetails(userDetails), studentController(userDetails) {}

void StudentView::displayView() {

    do {
        std::cout << "******************************" << std::endl;
        std::cout << "Welcome : " << userDetails.fullName << std::endl;
        std::cout << "1. Attempt a quiz" << std::endl;
        std::cout << "2. Quiz History" << std::endl;
        std::cout << "3. Logout" << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            attemptQuiz();
            break;
        case 2:
            std::cout << "Quiz History" << std::endl;
            break;
        case 3:
            std::cout << "Logging Out..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);

}

void StudentView::attemptQuiz() {

    int quizChoice;
    std::map<int, QuizDetails> quizMap = studentController.getAllQuizzes();

    std::cout << "******************************" << std::endl;
    std::cout << "Welcome : " << userDetails.fullName << std::endl;
    std::cout << "*** Choose Quiz ID ***" << std::endl;
    
    for (const auto& quiz : quizMap) {
        std::cout << "Quiz ID : " << quiz.first << " | " << "Quiz Name : " << quiz.second.quizName << std::endl;
    }
    std::cout << "******************************" << std::endl;

    std::cout << "Enter Quiz ID : ";
    std::cin >> quizChoice;
    std::cout << "******************************" << std::endl;

    QuizDetails selectedQuiz = quizMap[quizChoice];

    std::cout << "*** Selected Quiz Details ***" << std::endl;
    std::cout << "Quiz ID : " << selectedQuiz.quizId << " | " << "Quiz Name : " << selectedQuiz.quizName << std::endl;
    std::cout << "No. of Questions : " << selectedQuiz.numberOfQuestions << std::endl;

    std::cout << "******************************" << std::endl;
    std::cout << "*** Quiz Started! | All the Best! ***" << std::endl;
    
    int questionCounter = 1;
    for (QuestionDetails& question : selectedQuiz.questions) {
        std::cout << "******************************" << std::endl;
        std::cout << "Q" << questionCounter << ". " << question.questionText << std::endl;
        int optionCounter = 1;
        for (std::string& option : question.options) {
            std::cout << "    " << optionCounter << ". " << option << std::endl;
            optionCounter++;
        }

        std::cout << "Answer [1-4] : ";
        std::cin >> question.userEnteredOption;

        questionCounter++;
    }

    int score = 0;
    for (QuestionDetails& questions : selectedQuiz.questions) {
        if (questions.correctOption == questions.userEnteredOption) {
            score++;
        }
    }

    std::cout << "Score : " << score << std::endl;

    studentController.saveScore(score,quizChoice);


    

    return;



}