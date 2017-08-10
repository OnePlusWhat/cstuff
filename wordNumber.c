#include <stdio.h>

/**
 * Program to print the word of a given digit
 */

main() {
    printf("Enter a digit between 0-9: "); // Prompting the user
    int n;
    scanf("%d", &n); // Accepting input
    if (n<0 || n>9) { // Checking for invalid input
        printf("%d is not between 1-10", n);
    } else {
        switch(n) { // Printing the result after checking
            case 0: printf("Zero"); break;
            case 1: printf("One"); break;
            case 2: printf("Two"); break;
            case 3: printf("Three"); break;
            case 4: printf("Four"); break;
            case 5: printf("Five"); break;
            case 6: printf("Six"); break;
            case 7: printf("Seven"); break;
            case 8: printf("Eight"); break;
            case 9: printf("Nine"); break;    
        }
        // Simpler logic
        printf("\nNow using an array instead of switch-case structure\n");
        char c[10][5]={"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        printf("%d in words is %s", n, c[n]);
    }
    printf("\n");
}
