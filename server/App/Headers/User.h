#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

typedef struct userDetails{
    char fname[500];
    char lname[500];
    char uname[500];
    char phash[500];
} userDetails;

char* str2md5(const char *str);
userDetails getUser(char* uname);
int addUser(userDetails usr);
int login(char* uname, char* pwd);
int registerUsr(userDetails usr);