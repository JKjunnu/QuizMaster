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
            editQuiz();
            break;
        case 3:
            deleteQuiz();
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

void AdminView::editQuiz() {

    int quizChoice;
    std::map<int, QuizDetails> quizMap = adminController.getAllQuizzes();

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
    std::cout << "Quiz ID : " << selectedQuiz.quizId << " | " << "Quiz Name : " << selectedQuiz.quizName << " | " << "No. of Questions : " << selectedQuiz.numberOfQuestions << std::endl;

    std::cout << "******************************" << std::endl;

    std::string editQuizInput;
    while (editQuizInput != "yes" && editQuizInput != "no") {

        std::cout << "Edit Quiz Name? (yes) or (no) : ";
        std::cin >> editQuizInput;
        if (editQuizInput != "yes" && editQuizInput != "no") {
            std::cout << "Please check your input: (yes) or (no)" << std::endl;
        }
    }

    std::cout << "******************************" << std::endl;

    if (editQuizInput == "yes") {

        std::cout << "Quiz Name : " << selectedQuiz.quizName << std::endl;
        std::cout << "New Quiz Name : ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::getline(std::cin, selectedQuiz.quizName);

        //save quiz name to database here. done
        adminController.saveQuizName(selectedQuiz.quizId, selectedQuiz.quizName);
        //update the quiz map : done below
        quizMap = adminController.getAllQuizzes();
        selectedQuiz = quizMap[quizChoice];
        std::cout << "Quiz Name Saved!" << std::endl;
    }

    std::cout << "******************************" << std::endl;

    std::string editQuestionInput;
    
    while (editQuestionInput != "a" && editQuestionInput != "b") {
        std::cout << "Edit question (a) | Exit (b) : ";
        std::cin >> editQuestionInput;

        if (editQuestionInput != "a" && editQuestionInput != "b") {
            std::cout << " Please check your input: (a) or (b) " << std::endl;
        }
    }

    std::cout << "******************************" << std::endl;

    if (editQuestionInput == "b") {
        return;
    }

    //display questions only not options
    int questionCounter = 1;
    for (QuestionDetails& question : selectedQuiz.questions) {
        std::cout << "******************************" << std::endl;
        std::cout << "Q" << questionCounter << ". " << question.questionText << std::endl;
        questionCounter++;
    }

    std::cout << "******************************" << std::endl;

    //edit question
    if (editQuestionInput == "a") {

        int inputQuestionNumber;
        std::cout << "Select Question Number [1,2,3...] : ";
        std::cin >> inputQuestionNumber;

        std::string editQuestionTitleInput;
        while (editQuestionTitleInput != "yes" && editQuestionTitleInput != "no") {

            std::cout << "Edit Question Title? (yes) or (no) : ";
            std::cin >> editQuestionTitleInput;
            if (editQuestionTitleInput != "yes" && editQuestionTitleInput != "no") {
                std::cout << "Please check your input: (yes) or (no)" << std::endl;
            }
        }

        std::cout << "******************************" << std::endl;

        if (editQuestionTitleInput == "yes") {

            std::cout << "Question Title : " << selectedQuiz.questions[inputQuestionNumber-1].questionText << std::endl;
            std::cout << "New Question Title : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, selectedQuiz.questions[inputQuestionNumber-1].questionText);

            //save question title to database here. Done
            adminController.saveQuestionTitle(selectedQuiz.questions[inputQuestionNumber - 1].questionId, selectedQuiz.questions[inputQuestionNumber - 1].questionText);
            //update the quiz map : done below
            quizMap = adminController.getAllQuizzes();
            selectedQuiz = quizMap[quizChoice];
            std::cout << "Question Details Saved!" << std::endl;
        }

        std::cout << "******************************" << std::endl;

        

        //display options for the question [1,2,3,4]
        //display correct option [5]


        int optionCounter = 1;
        for (std::string& option : selectedQuiz.questions[inputQuestionNumber-1].options) {
            std::cout << "Option " << optionCounter << ". " << option << std::endl;
            optionCounter++;
        }

        std::cout << "Correct Option : " << selectedQuiz.questions[inputQuestionNumber-1].correctOption << std::endl;

        std::cout << "******************************" << std::endl;

        int editOptionInput = 0;
        while (editOptionInput < 1 || editOptionInput > 6) {

            std::cout << "To Edit Option Choose [1-4] | To Edit Correct Option Choose [5] | To Exit [6] : ";
            std::cin >> editOptionInput;
            if (editOptionInput < 1 || editOptionInput > 6) {
                std::cout << "Please check your input !" << std::endl;
            }
        }

        std::cout << "******************************" << std::endl;

        if (editOptionInput == 6) {
            return;
        }

        if (editOptionInput >= 1 && editOptionInput <= 4) {

            std::cout << " Option " << editOptionInput << ". " << selectedQuiz.questions[inputQuestionNumber - 1].options[editOptionInput - 1] << std::endl;
            std::cout << " New Option : ";
            std::string newOption;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, newOption);

            //save to database done
            adminController.saveOption(selectedQuiz.questions[inputQuestionNumber - 1].questionId, editOptionInput, newOption);
            quizMap = adminController.getAllQuizzes();
            selectedQuiz = quizMap[quizChoice];
            std::cout << "Option Details Saved!" << std::endl;

        }

        if (editOptionInput == 5) {
            std::cout << "Correct Option : " << selectedQuiz.questions[inputQuestionNumber - 1].correctOption << std::endl;
            int newCorrectOption;
            std::cout << "New Correct Option : ";
            std::cin >> newCorrectOption;

            //save to database
            adminController.saveCorrectOption(selectedQuiz.questions[inputQuestionNumber - 1].questionId, newCorrectOption);
            quizMap = adminController.getAllQuizzes();
            selectedQuiz = quizMap[quizChoice];
            std::cout << "Correct Option Saved!" << std::endl;
        }

        std::cout << "******************************" << std::endl;

    }

    ////add question
    //if (editQuestionInput == "b") {


    //}

    return;
    
    
}


void AdminView::deleteQuiz() {

    int quizChoice;
    std::map<int, QuizDetails> quizMap = adminController.getAllQuizzes();

    std::cout << "******************************" << std::endl;
    std::cout << "Welcome : " << userDetails.fullName << std::endl;
    std::cout << "*** Choose Quiz ID ***" << std::endl;

    for (const auto& quiz : quizMap) {
        std::cout << "Quiz ID : " << quiz.first << " | " << "Quiz Name : " << quiz.second.quizName << std::endl;
    }
    std::cout << "******************************" << std::endl;

    std::cout << "Enter Quiz ID  to delete: ";
    std::cin >> quizChoice;
    std::cout << "******************************" << std::endl;

    QuizDetails selectedQuiz = quizMap[quizChoice];

    std::cout << "*** Selected Quiz Details ***" << std::endl;
    std::cout << "Quiz ID : " << selectedQuiz.quizId << " | " << "Quiz Name : " << selectedQuiz.quizName << " | " << "No. of Questions : " << selectedQuiz.numberOfQuestions << std::endl;

    std::cout << "******************************" << std::endl;

    std::string confirmDelete;
    while (confirmDelete != "yes" && confirmDelete != "no") {

        std::cout << "Are you sure? (yes) or (no) : ";
        std::cin >> confirmDelete;
        if (confirmDelete != "yes" && confirmDelete != "no") {
            std::cout << "Please check your input: (yes) or (no)" << std::endl;
        }
    }

    if (confirmDelete == "yes") {

        adminController.deleteQuiz(selectedQuiz.quizId);
        std::cout << "Deleted quiz!" << std::endl;

    }

    if (confirmDelete == "no") {
        std::cout << "No changes made!" << std::endl;
    }

    std::cout << "******************************" << std::endl;

    return;

}

    
