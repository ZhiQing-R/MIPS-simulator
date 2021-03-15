#include <stdio.h>
#include <string.h>
#include "freader.h"
#include "reg_inst.h"

extern long realm;
void printBin(unsigned int number){
    char bin_code[33];
	for(int i = 0; i < 32; i++){
		bin_code[i] = '0';
    }
    int ptr = 31;
    int remainder;
    unsigned int curr_num = number;
    while(curr_num > 0){
        remainder = curr_num % 2;
        bin_code[ptr--] = remainder+48;
        curr_num = curr_num / 2;
    }
	*(bin_code + 32) = '\0';
    printf("%s\n",bin_code);
}

/*int main(){
    char in;
    FILE* read_in = stdin;
    FILE* mips_code = fopen("code.txt","w");
    in = getc(read_in);
    while (!feof(read_in))
    {
        putc(in,mips_code);
        in = getc(read_in);
    }
    fclose(read_in);
    fclose(mips_code);
    mips_code = fopen("code.txt","r");
    int code;
    regInit();
    instInit();
    labelCollect(mips_code);
    fseek(mips_code, 0, SEEK_SET);
    char token[128];
    while(1){
        getToken(mips_code,token);
        if(strcmp(token,".text") == 0) break;
    }
    int inst_cnt = 0;
    while(!feof(mips_code)){
        getToken(mips_code,token);
        if(instSearch(token) >= 0){
            inst_cnt++;
            code = encode(mips_code,token,inst_cnt);
            printBin(code);
        }
    }
    fclose(mips_code);
    return 0;
}*/

int* assemble(long fp, FILE* src){
    int* PC = (int*)fp;
    char in;
    FILE* mips_code = fopen("code.txt","w");
    in = getc(src);
    while (!feof(src))
    {
        putc(in,mips_code);
        in = getc(src);
    }
    fclose(mips_code);
    mips_code = fopen("code.txt","r");
    int code;
    regInit();
    instInit();
    labelCollect(mips_code);
    fseek(mips_code, 0, SEEK_SET);
    char token[128];
    while(1){
        getToken(mips_code,token);
        if(strcmp(token,".text") == 0) break;
    }
    int inst_cnt = 0;
    while(!feof(mips_code)){
        getToken(mips_code,token);
        if(strcmp(token,".data") == 0) break;
        if(instSearch(token) >= 0){
            inst_cnt++;
            code = encode(mips_code,token,inst_cnt);
            printBin(code);
            *PC = code;
            PC = PC + 1;
        }
    }
    fclose(mips_code);
    return PC;
}

int writeData(FILE* src, long begin){
    char* PC = (char*)begin;
    char* word;
    char token[128];
    char tmp;
    int len, cursor;
    while(!feof(src)){
        getToken(src,token);
        if(strcmp(token,".data") == 0) break;
    }
    while (!feof(src)){
        getToken(src,token);
        if(*token != '.'){
            continue;
        }else{
            char lastChar = token[strlen(token)-1];
            if(lastChar == 't') break;
            switch(lastChar){
                case 'z':   //.asciiz
                    while((tmp = getc(src)) != '\"'){}
                    while((tmp = getc(src)) != '\"'){
                        if(tmp == '\\'){
                            tmp = getc(src);
                            switch(tmp){
                                case 'n':
                                    tmp = '\n';
                                    break;
                                case 't':
                                    tmp = '\t';
                                    break;
                                case 'v':
                                    tmp = '\v';
                                    break;
                                case '\\':
                                    tmp = '\\';
                                    break;
                                case '\'':
                                    tmp = '\'';
                                    break;
                                case '\"':
                                    tmp = '\"';
                                    break;
                                case '0':
                                    tmp = '\0';
                                    break;
                                default:
                                    break;
                            }
                        }
                        *PC = tmp;
                        PC = PC + 1;
                    }
                    *PC = '\0';
                    PC = (char*)(((long)PC & 0xFFFFFFFFFFFFFFFC) + 4);
                    break;
                case 'i':   //.ascii
                    while((tmp = getc(src)) != '\"'){}
                    while((tmp = getc(src)) != '\"'){
                        if(tmp == '\\'){
                            tmp = getc(src);
                            switch(tmp){
                                case 'n':
                                    tmp = '\n';
                                    break;
                                case 't':
                                    tmp = '\t';
                                    break;
                                case 'v':
                                    tmp = '\v';
                                    break;
                                case '\\':
                                    tmp = '\\';
                                    break;
                                case '\'':
                                    tmp = '\'';
                                    break;
                                case '\"':
                                    tmp = '\"';
                                    break;
                                case '0':
                                    tmp = '\0';
                                    break;
                                default:
                                    break;
                            }
                        }
                        *PC = tmp;
                        PC = PC + 1;
                    }
                    PC = PC - 1;
                    PC = (char*)(((long)PC & 0xFFFFFFFFFFFFFFFC) + 4);
                    break;
                case 'e':{   //.byte
                    cursor = 0;
                    char num;
                    char d[2] = ",";
                    while((tmp = getc(src)) != '\n'){
                        token[cursor++] = tmp;
                    }
                    token[cursor] = '\0';
                    word = strtok(token,d);
                    while(word != NULL){
                        if(*word == '0' && (*(word+1) == 'x' || *(word + 1) == 'X')){
                            num = strtol(word,NULL,16);
                        }else{
                            num = strtol(word,NULL,10);
                        }
                        *PC = num;
                        PC = PC + 1;
                        word = strtok(NULL,d);
                    }
                    PC = PC - 1;
                    PC = (char*)(((long)PC & 0xFFFFFFFFFFFFFFFC) + 4);
                    break;
                }
                case 'f':{  //.half
                    cursor = 0;
                    short num;
                    short* p;
                    char d[2] = ",";
                    while((tmp = getc(src)) != '\n'){
                        token[cursor++] = tmp;
                    }
                    token[cursor] = '\0';
                    word = strtok(token,d);
                    while(word != NULL){
                        if(*word == '0' && (*(word+1) == 'x' || *(word + 1) == 'X')){
                            num = strtol(word,NULL,16);
                        }else{
                            num = strtol(word,NULL,10);
                        }
                        p = (short*)PC;
                        *p = num;
                        PC = PC + 2;
                        word = strtok(NULL,d);
                    }
                    PC = PC - 2;
                    PC = (char*)(((long)PC & 0xFFFFFFFFFFFFFFFC) + 4);
                    break;
                }
                case 'd':{  //.word
                    cursor = 0;
                    int num;
                    int* w;
                    char d[2] = ",";
                    while((tmp = getc(src)) != '\n'){
                        token[cursor++] = tmp;
                    }
                    token[cursor] = '\0';
                    word = strtok(token,d);
                    while(word != NULL){
                        if(*word == '0' && (*(word+1) == 'x' || *(word + 1) == 'X')){
                            num = strtol(word,NULL,16);
                        }else{
                            num = strtol(word,NULL,10);
                        }
                        w = (int*)PC;
                        *w = num;
                        PC = PC + 4;
                        word = strtok(NULL,d);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    reg_list[28].val = (long) PC - realm;
}