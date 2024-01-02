#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct userDetails{
    char fname[500];
    char lname[500];
    char uname[500];
    char phash[500];
} userDetails;

char* signin();
char* signup();