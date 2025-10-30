#include <stdbool.h>
#include "process.h"

static bool is_movie_file(char* dirName)
{
    // check if begins with "movies_"
    if(strncmp(dirName, "movies_", 7) != 0)
    {
        return false;
    }

    // check if ends with ".csv"
    char* extension_start = strrchr(dirName, '.');
    if (extension_start == NULL || strcmp(extension_start, ".csv") != 0)
    {
        return false;
    }

    return true;
}

static void find_largest_file(char* filepath)
{
    DIR* currDir;
    struct dirent* entry;
    struct stat dirStat;

    off_t max_bytes = 0;
    char largest_filepath[256];
    currDir = opendir(".");

    while((entry = readdir(currDir)) != NULL)
    {
        stat(entry->d_name, &dirStat);

        if(S_ISREG(dirStat.st_mode) && is_movie_file(entry->d_name))
        {
            if (dirStat.st_size > max_bytes)
            {
                max_bytes = dirStat.st_size;
                strcpy(largest_filepath, entry->d_name);
            }
        }
    }

    strcpy(filepath, largest_filepath);
    printf("largest file was %s with %lld bytes\n", filepath, max_bytes);
}

static void find_smallest_file(char* filepath)
{
    DIR* currDir;
    struct dirent* entry;
    struct stat dirStat;

    off_t min_bytes = 0;
    char smallest_filepath[256];
    currDir = opendir(".");

    while((entry = readdir(currDir)) != NULL)
    {
        stat(entry->d_name, &dirStat);

        if(S_ISREG(dirStat.st_mode) && is_movie_file(entry->d_name))
        {
            if (dirStat.st_size < min_bytes || min_bytes == 0)  //replace the first find with appropriate bytes
            {
                min_bytes = dirStat.st_size;
                strcpy(smallest_filepath, entry->d_name);
            }
        }
    }

    strcpy(filepath, smallest_filepath);
    printf("smallest file was %s with %lld bytes\n", filepath, min_bytes);

}

static bool find_requested_file(char* filepath)
{
    printf("Enter the complete file name: ");
    scanf("%s", filepath);

    DIR* currDir;
    struct dirent* entry;
    struct stat dirStat;

    currDir = opendir(".");

    while((entry = readdir(currDir)) != NULL)
    {
        if(strcmp(entry->d_name, filepath) == 0)
        {
            printf("requested file %s\n", filepath);
            return true;
        }
    }

    printf("The file %s was not found. Try again\n", filepath);
    return false;

}


void process_select()
{
    int usr_input = 0;
    char file_name[256];
    file_name[0] = '\0';        // initialize an empty string

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
                find_largest_file(file_name);
                break;
            case 2:
                find_smallest_file(file_name);
                break;
            case 3:
                find_requested_file(file_name);
                break;
            default:
                printf("You entered an incorrect choice. Try again.\n");
                break;
        }
    }
}