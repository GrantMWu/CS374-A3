#include <stdio.h>
#include <stdlib.h>
#include "process.h"

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
                process_select();
                break;
            case 2:
                break;
            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    }
}