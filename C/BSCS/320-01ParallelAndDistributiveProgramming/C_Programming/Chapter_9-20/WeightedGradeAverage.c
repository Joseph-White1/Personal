// Joseph White
// 11/15/2023
// CSCI 320: Week 3 Assignment

#include <stdio.h>

int main()
{
    float testScore, quizScore, homeworkAverage, testTotal = 0.0,
        quizTotal = 0.0, testAverage = 0.0, quizAverage = 0.0, finalGrade = 0.0;
    int testCount = 0, quizCount = 0;

    // Collect test scores
    while(1)
    {
        printf("Enter test scores (enter -1 to finish): ");
        scanf("%f", &testScore);
        if(testScore == -1)
        {
            break;
        }
        if(testScore >= 0 && testScore <= 100)
        {
            testTotal += testScore;
            testCount++;
        }
        else
        {
            printf("Invalid score. Please enter a value between 0 and 100.\n");
        }
    }
    printf("\n");

    // Collect quiz scores
    while(1)
    {
        printf("Enter quiz scores (enter -1 to finish): ");
        scanf("%f", &quizScore);
        if(quizScore == -1)
        {
            break;
        }
        if(quizScore >= 0 && quizScore <= 100)
        {
            quizTotal += quizScore;
            quizCount++;
        }
        else
        {
            printf("Invalid score. Please enter a value between 0 and 100.\n");
        }
    }
    printf("\n");

    // Collect homework average
    while(1)
    {
        printf("Enter homework average: ");
        scanf("%f", &homeworkAverage);
        if(homeworkAverage >= 0 && homeworkAverage <= 100)
        {
            break;
        }
        else
        {
            printf("Invalid score. Please enter a value between 0 and 100.\n");
        }
    }
    printf("\n");

    // Calculate averages and final grade
    if(testCount > 0)
    {
        testAverage = testTotal / testCount;
    }
    if(quizCount > 0)
    {
        quizAverage = quizTotal / quizCount;
    }
    finalGrade = (testAverage * 0.6) + (quizAverage * 0.35) + (homeworkAverage * 0.05);

    // Output results
    printf("Test Average: %.2f\n", testAverage);
    printf("Quiz Average: %.2f\n", quizAverage);
    printf("Final Weighted Grade: %.2f\n", finalGrade);
    printf("\n");

    return 0;
}
