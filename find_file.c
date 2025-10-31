#include "find_file.h"

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

void find_largest_file(char* filepath)
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
    closedir(currDir);
}

void find_smallest_file(char* filepath)
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
    closedir(currDir);
}

bool requested_file_found(char* filepath)
{
    printf("Enter the complete file name: ");
    scanf("%s", filepath);

    DIR* currDir;
    struct dirent* entry;

    currDir = opendir(".");

    while((entry = readdir(currDir)) != NULL)
    {
        if(strcmp(entry->d_name, filepath) == 0)
        {
            closedir(currDir);
            return true;
        }
    }

    closedir(currDir);
    return false;

}