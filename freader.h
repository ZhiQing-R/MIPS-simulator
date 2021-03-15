#ifndef FILE_READER
#define FILE_READER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct label{
    char name[64];
    int address;
};

void getToken(FILE* code, char* dest);
void labelCollect(FILE* src);
int encode(FILE* src, char* inst, int inst_cnt);
int writeData(FILE* src, long begin);
int labelSearch(char* label);
int* assemble(long fp, FILE* src);

extern struct label label_list[32];
extern int label_cnt;
#endif