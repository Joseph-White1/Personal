// Joseph White
// 11/16/2023
// CSCI 320: Week 4 Assignment

#include <stdio.h>

double processDeposit(double balance);
double processCheck(double balance);

int main()
{
    double balance;
    int choice;

    printf("Enter the initial balance: ");
    scanf("%lf", &balance);

    do
    {
        printf("\nChoose an option:\n");
        printf("1. Deposit\n");
        printf("2. Write a check\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                balance = processDeposit(balance);
                break;
            case 2:
                balance = processCheck(balance);
                break;
            case 3:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 3);

    printf("\nFinal balance: $%.2f\n", balance);
    printf("\n");
    return 0;
}

double processDeposit(double balance)
{
    double depositAmount;

    printf("Enter deposit amount: ");
    scanf("%lf", &depositAmount);

    if (depositAmount < 0)
    {
        printf("Invalid amount. Deposit must be a positive number.\n");
    }
    else
    {
        balance += depositAmount;
        printf("New balance: $%.2f\n", balance);
    }
    return balance;
}

double processCheck(double balance)
{
    double checkAmount;

    printf("Enter check amount: ");
    scanf("%lf", &checkAmount);

    while (checkAmount < 0 || (balance - checkAmount) < 0)
    {
        if (checkAmount < 0)
        {
            printf("Invalid amount. Check must be a positive number.\n");
        }
        else
        {
            printf("Insufficient funds. Check cannot be processed.\n");
        }
        return balance;
    }

    balance -= checkAmount;
    printf("New balance: $%.2f\n", balance);

    return balance;
}
