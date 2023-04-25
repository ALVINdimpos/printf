#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 10
#define MAX_ANSWERS 4
#define MAX_QUESTION_LENGTH 100
#define MAX_ANSWER_LENGTH 50

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char answers[MAX_ANSWERS][MAX_ANSWER_LENGTH];
    int correctAnswerIndex;
} Question;

void askQuestion(int* currentIndex, int* score, Question* questions, int numQuestions);

void runQuiz(Question* questions, int numQuestions) {
    int score = 0;
    int currentIndex = 0;

    askQuestion(&currentIndex, &score, questions, numQuestions); // Call askQuestion for the first time

    printf("Quiz complete. Your score is %d out of %d.\n", score, numQuestions);
}

void askQuestion(int* currentIndex, int* score, Question* questions, int numQuestions) {
    const char* question = questions[*currentIndex].question;
    const char answers[MAX_ANSWERS][MAX_ANSWER_LENGTH];
    memcpy(answers, questions[*currentIndex].answers, sizeof(answers));
    int correctAnswerIndex = questions[*currentIndex].correctAnswerIndex;

    printf("Question %d: %s\n", *currentIndex + 1, question);
    for (size_t i = 0; i < MAX_ANSWERS; ++i) {
        printf("%d. %s\n", i + 1, answers[i]);
    }

    int userAnswer;
    printf("Enter your answer (number): ");
    scanf("%d", &userAnswer);

    if (userAnswer == correctAnswerIndex + 1) {
        printf("Correct!\n");
        (*score)++;
    } else {
        printf("Incorrect.\n");
    }
    (*currentIndex)++;

    if (*currentIndex < numQuestions) {
        askQuestion(currentIndex, score, questions, numQuestions);  // Call askQuestion recursively
    }
}

int main() {
    Question questions[MAX_QUESTIONS] = {
        {
            "What is the capital of France?",
            {"Paris", "London", "Berlin", "Madrid"},
            0
        },
        {
            "What is the largest country in the world by land area?",
            {"China", "United States", "Russia", "Canada"},
            2
        },
        {
            "What is the smallest continent by land area?",
            {"North America", "Europe", "Australia", "South America"},
            2
        }
    };

    runQuiz(questions, 3);

    return 0;
}
