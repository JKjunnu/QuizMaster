#include "view/AdminView.h"
#include <limits>

AdminView::AdminView(UserDetails& userDetails) : userDetails(userDetails), adminController(userDetails) {}

void AdminView::displayView() {

    do {
        std::cout << "******************************" << std::endl;
        std::cout << "Welcome : " << userDetails.fullName << std::endl;
        std::cout << "1. Create Quiz" << std::endl;
        std::cout << "2. Edit Quiz" << std::endl;
        std::cout << "3. Delete Quiz" << std::endl;
        std::cout << "4. Logout" << std::endl;
        std::cout << "******************************" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            createQuiz();
            break;
        case 2:
            std::cout << "Edit Quiz" << std::endl;
            break;
        case 3:
            std::cout << "Delete Quiz" << std::endl;
            break;
        case 4:
            std::cout << "Logging Out..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

}

void AdminView::createQuiz() {

    QuizDetails quizDetails;
    std::string noOfQuestions;
    
    std::cout << "******************************" << std::endl;
    std::cout << "Welcome : " << userDetails.fullName << std::endl;
    std::cout << "*** Create Quiz ***" << std::endl;
    std::cout << "Quiz Name : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::getline(std::cin, quizDetails.quizName);
    std::cout << "No. of Questions :";
    std::cin >> noOfQuestions;
    quizDetails.numberOfQuestions = std::stoi(noOfQuestions);
    std::cout << "******************************" << std::endl;

    // Question input

    
    for (int i = 0; i < quizDetails.numberOfQuestions; i++) {
        QuestionDetails question;
        std::cout << "******************************" << std::endl;
        std::cout << "Question " << i + 1 << " : ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::getline(std::cin, question.questionText);

        // Options input

        for (int j = 0; j < 4; j++) {
            std::string option;
            std::cout << "Option " << j + 1 << " : ";
            std::getline(std::cin, option);
            question.options.push_back(option);
        }

        std::string correctOption;
        std::cout << "Correct Option (1-4) : ";
        std::cin >> correctOption;
        question.correctOption = std::stoi(correctOption);

        quizDetails.questions.push_back(question);
        std::cout << "******************************" << std::endl;
    }

    adminController.saveQuiz(quizDetails);

    return;
}

    
