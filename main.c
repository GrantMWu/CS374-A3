#include <stdio.h>
#include <stdlib.h>

#include "find_file.h"
#include "process.h"

void select_filesearch_method(char* file_name)
{
    int usr_input = 0;
    file_name[0] = '\0';        // initialize an empty string

    while(usr_input < 1 || usr_input > 3)
    {
        printf
        (
            "\nWhich file you want to process?\n"
            "Enter 1 to pick the largest file\n"
            "Enter 2 to pick the smallest file\n"
            "Enter 3 to specify the name of a file\n"
            "\nEnter a choice from 1 to 3: "
        );

        scanf("%d", &usr_input);

        switch (usr_input)
        {
            case 1:
                find_largest_file(file_name);
                break;

            case 2:
                find_smallest_file(file_name);
                break;

            case 3:
                if (requested_file_found(file_name))
                {
                    // process file here
                    printf("requested file %s\n", file_name);
                }
                else
                {
                    usr_input = 0;
                    printf("The file %s was not found. Try again\n", file_name);
                }

                break;

            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    }
}

int main(){
    int usr_input = 0;
    char file_name[256];

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
                select_filesearch_method(file_name);
                processFile(file_name);
                break;

            case 2:
                break;

            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    }
}