#ifndef FILE_READER
#define FILE_READER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct label{
    char name[16];
    int address;
};

void getToken(FILE* code, char* dest);
void labelCollect(FILE* src);
int encode(FILE* src, char* inst);
int labelSearch(char* label);

extern struct label label_list[64];
extern int label_cnt;
#endif