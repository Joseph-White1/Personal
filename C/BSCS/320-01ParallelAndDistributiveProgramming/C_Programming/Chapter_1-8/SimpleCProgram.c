// Joseph White
// 10/29/2023
// CSCI 320: Week 1 Assignment

#include <stdio.h>

int main() {
    char name[50];
    int month, day, year;
    char place[50];
    char dessert[50];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your birthdate (use integers in MM/DD/YY formatting): ");
    scanf(" %d/%d/%d", &month, &day, &year);

    printf("Enter your favorite place to visit: ");
    scanf(" %s", place);

    printf("Enter your favorite dessert: ");
    scanf(" %s", dessert);

    printf("\nHello %s,\n", name);
    printf("Maybe you could visit %s for %d days", place, day);
    printf(" and enjoy %d servings of %s while there.\n", month, dessert);

    return 0;
}
