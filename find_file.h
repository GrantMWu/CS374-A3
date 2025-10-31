#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void find_largest_file(char* file_name);
void find_smallest_file(char* file_name);
bool requested_file_found(char* file_name);