#include "process.h"

static void freeYearFiles(yearFile_t* head)
{
    yearFile_t* tmp;

    while (head != NULL)
    {
        close(head->yearfd);
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void processFile(char* moviefp)
{
    printf("Now processing the chosen file named %s\n", moviefp);

    char dirpath[19];
    createDir(dirpath);

    printf("Created directory with name %s\n", dirpath);

    char *currLine = NULL;
    size_t len = 0;

    // Open the specified file for reading only
    FILE *movieFile = fopen(moviefp, "r");
    yearFile_t* head = NULL;

    getline(&currLine, &len, movieFile);    // skip header

    char* title = NULL;
    int year = 0;
    char* yearfp = NULL;

    // read each line, call getFile to get a node, then add to linked list
    while(getline(&currLine, &len, movieFile) != -1)
    {
        parseLine(currLine, &title, &year);

        yearfp = realloc(yearfp, 19 + strlen(title) + 2);
        sprintf(yearfp, "%s/%d.txt", dirpath, year);

        int fd = getFile(yearfp, &head, year);


        write(fd, title, strlen(title));
    }

    // Free the memory 
    free(title);
    free(yearfp);
    free(currLine);
    freeYearFiles(head);

    // Close the file
    fclose(movieFile);
}


void parseLine(char* line, char** title, int* year)
{
    char* savePtr;
    char* token;

    // first token for title
    token = strtok_r(line, ",", &savePtr);
    *title = realloc(*title, strlen(token) + 1);
    if (title == NULL)
    {
        printf("title reallocation unsuccessful");
        free(title);
        exit(1);
    }
    else
    {
        // strcpy(*title, token);
        sprintf(*title, "%s\n", token);
    }
    // second token for year
    token = strtok_r(NULL, ",", &savePtr);
    *year = atoi(token);
}

int getFile(char* fpath, yearFile_t** head, int year)
{
    // search each yearFile for a year matching node
    yearFile_t* curr = *head;
    yearFile_t* prev = NULL;

    while (curr) 
    {
        if (curr->year == year)
        {
            return curr->yearfd;      
        }

        prev = curr;
        curr = curr->next;
        
    }

    // no matching year - create new node
    yearFile_t* fptr = malloc(sizeof(yearFile_t));
    fptr->year = year;
    fptr->next = NULL;
    fptr->yearfd = open(fpath, O_WRONLY | O_CREAT | O_APPEND, 0640);
    
    if (fptr->yearfd == -1) 
    {
        printf("open() has failed on %s\n", fpath);
        perror("Error");
        exit(1);
    }

    if(!prev)       // first node
    {
        *head = fptr;
        return fptr->yearfd;
    }
    else
    {
        prev->next = fptr;
        return fptr->yearfd;
    }
    
}

void createDir(char* dirpath)
{
    //generate a random number for extension
    srand(time(NULL));
    int r = rand() % 9999;
    sprintf(dirpath, "%s%d", "wugr.movies.", r);
    
    mkdir(dirpath, 0750);
}
