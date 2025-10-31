#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct yearFile_t
{
    int year;
    int yearfd;     // file descriptor for yearfile
    struct yearFile_t* next;
} yearFile_t;

/*
 * Function: processFile
 *   Processes a movie file 
 * 
 */
void processFile(char* filepath);

int getFile(char* dirpath, yearFile_t** head, int year);

void parseLine(char* line, char** title, int* year);
// void parseLine(char* line, char* title, int year);

/*
 * Function: createDir
 *   Generates new directory to store processed file
 * 
 * The new directory will be in the format wugr_movies.random
 * where random will be a random number from 0-99999
 */
void createDir(char* dirpath);


/*
 * Function: createFile
 *    creates a new file of format YYYY.csv
 *    adds a yearFile node to the yearFile linked list 
 * 
 */
void createFile();

/*
 * Function: appendFile
 *    writes a movie title to a year file
 * 
 * 
 * 
 */
void writeFile(int fd, char* title);