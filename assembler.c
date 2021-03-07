#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freader.h"
#include "reg_inst.h"

void printBin(int number){
    char bin_code[33];
	for(int i = 0; i < 32; i++){
		bin_code[i] = '0';
    }
    int ptr = 31;
    int remainder;
    int curr_num = number;
    while(curr_num > 0){
        remainder = curr_num % 2;
        bin_code[ptr--] = remainder+48;
        curr_num = curr_num / 2;
    }
	*(bin_code + 32) = '\0';
    printf("%s\n",bin_code);
}

int main(){
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
    char token[16];
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
}

int* assemble(long fp){
    int* PC = (int*)fp;
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
    char token[16];
    while(1){
        getToken(mips_code,token);
        if(strcmp(token,".text") == 0) break;
    }
    int inst_cnt;
    while(!feof(mips_code)){
        getToken(mips_code,token);
        if(instSearch(token) >= 0){
            inst_cnt++;
            code = encode(mips_code,token,inst_cnt);
            *PC = code;
            PC = PC + 1;
        }
    }
    fclose(mips_code);
    return PC;
}