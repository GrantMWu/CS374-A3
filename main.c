#include <stdio.h>
#include <stdlib.h>

void select_process(){
    int usr_input = 0;

    while(usr_input < 1 || usr_input > 3)
    {
        printf
        (
            "\nWhich file you want to process?\n"
            "Enter 1 to pick the largest file\n"
            "Enter 2 to pick the smallest file\n"
            "Enter 3 to specify the name of a file\n"
            "Enter a choice from 1 to 3: "
        );

        scanf("%d", &usr_input);

        switch (usr_input)
        {
            case 1:
                // pick largest file
                break;
            case 2:
                // pick smallest file
                break;
            case 3:
                // specify file name
                break;
            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    }
}

int main(){
    int usr_input = 0;

    while(usr_input != 2)
    {
        printf
        (
            "\n1. Select file to process\n" 
            "2. Exit the program\n"
        );

        printf("\nEnter a choice from 1 or 2: ");
        scanf("%d", &usr_input);
        
        switch (usr_input)
        {
            case 1:
                select_process();
                break;
            case 2:
                break;
            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    }
}