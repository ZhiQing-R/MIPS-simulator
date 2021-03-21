#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freader.h"
#include "reg_inst.h"

struct label label_list[32];
int label_cnt = 0;

void getToken(FILE* code, char* dest){
    char token[128];
    int word_len = 0;
    char chara;
    while(!feof(code)){
        chara = getc(code);
        if(chara == '#'){
            while(getc(code) != '\n'){}
            if(word_len == 0){
                getToken(code,dest);
                return;
            }else break;
        }else if(chara == ' ' || chara == '\n' || chara == ',' || chara == '\t'){
            chara = getc(code);
            while(chara == '\n' || chara == ' ' || chara == '\t'){
                chara = getc(code);
            }
            ungetc(chara,code);
            if(word_len == 0){
                getToken(code,dest);
                return;
            }else break;
        }else if(chara == -1){
            break;
        }else{
            token[word_len++] = chara;
        }
    }
    token[word_len] = '\0';
    strncpy(dest,token,word_len+1);
}

void labelCollect(FILE* src){
    char temp;
    char token[64];
    int inst_cnt = 0;
    int len;
    while(1){
        getToken(src,token);
        if(strcmp(token,".text") == 0) break;
    }
    getToken(src,token);
    while(!feof(src)){
        len = strlen(token);
        if(token[len-1] == ':'){    //Case when find lable
            strncpy(label_list[label_cnt].name,token,len-1);
            label_list[label_cnt++].address = inst_cnt;
        }else if(instSearch(token) >= 0){   //Case when find an instruction
            inst_cnt++;
        }else;
        getToken(src,token);
    }

}

int labelSearch(char* label){
    for(int i = 0; i < label_cnt; i++){
        if(strcmp(label,label_list[i].name) == 0){
            return label_list[i].address;
        }
    }
    return -1;
}
int encode(FILE* src, char* inst, int inst_cnt){
    int op, rs, rt, rd, address, shamt, func;
    short imm;
    char* label;
    enum INSTRUCTION inst_num = instSearch(inst);
    char token[64];
    int m_code;
    switch (inst_num)
    {
    case ADD:
    case ADDU:
    case AND:
    case MUL:
    case NOR:
    case OR:
    case SLLV:
    case SUB:
    case SUBU:
    case XOR:
    case SLT:
    case SLTU:
        shamt = 0;
        getToken(src,token);
        rd = regSearch(token);
        getToken(src,token);
        rs = regSearch(token);
        getToken(src,token);
        rt = regSearch(token);
        break;
    case ADDI:
    case ADDIU:
    case ANDI:
    case ORI:
    case XORI:
    case SLTI:
    case SLTIU:
        getToken(src,token);
        rt = regSearch(token);
        getToken(src,token);
        rs = regSearch(token);
        getToken(src,token);
        imm = atoi(token);
        break;
    case CLO:
    case CLZ:
        shamt = 0;
        getToken(src,token);
        rd = regSearch(token);
        getToken(src,token);
        rs = regSearch(token);
        rt = 0;
        break;
    case DIV:
    case DIVU:
    case MULT:
    case MULTU:
    case MADD:
    case MADDU:
    case MSUB:
    case MSUBU:
    case TEQ:
    case TNE:
    case TGE:
    case TGEU:
    case TLT:
    case TLTU:
        shamt = 0;
        getToken(src,token);
        rs = regSearch(token);
        getToken(src,token);
        rt = regSearch(token);
        rd = 0;
        break;
    case SLL:
    case SRA:
    case SRL:
        rs = 0;
        getToken(src,token);
        rd = regSearch(token);
        getToken(src,token);
        rt = regSearch(token);
        getToken(src,token);
        shamt = atoi(token);
        break;
    case SRAV:
    case SRLV:
        shamt = 0;
        getToken(src,token);
        rd = regSearch(token);
        getToken(src,token);
        rt = regSearch(token);
        getToken(src,token);
        rs = regSearch(token);
        break;
    case LUI:
        rs = 0;
        getToken(src,token);
        rt = regSearch(token);
        getToken(src,token);
        imm = atoi(token);
        break;
    case BEQ:
    case BNE:{
        getToken(src,token);
        rt = regSearch(token);
        getToken(src,token);
        rs = regSearch(token);
        getToken(src,token);
        int labelIndex = labelSearch(token);
        if(labelIndex == -1){
            imm = atoi(token);
        }else{
            imm = labelIndex - inst_cnt;
        }
        break;
    }
    case BGEZ:
    case BGEZAL:
    case BGTZ:
    case BLEZ:
    case BLTZ:
    case BLTZAL:
    case TEQI:
    case TNEI:
    case TGEI:
    case TGEIU:
    case TLTI:
    case TLTIU:{
        getToken(src,token);
        rs = regSearch(token);
        getToken(src,token);
        int labelIndex = labelSearch(token);
        if(labelIndex == -1){
            if(token[0] == '0' && (token[1] == 'x' || token[1] == 'X')){
                imm = strtol(token,NULL,16);
            }else{
                imm = atoi(token);
            }
        }else{
            imm = labelIndex - inst_cnt;
        }
        break;
    }
    case J:
    case JAL:{
        getToken(src,token);
        int labelIndex = labelSearch(token);
        if(labelIndex == -1){
            address = atoi(token) + + 0x100000;
        }else{
            address = labelIndex + 0x100000;
        }
        break;
    }
    case JALR:
        getToken(src,token);
        rs = regSearch(token);
        getToken(src,token);
        rd = regSearch(token);
        rt = 0;
        shamt = 0;
        break;
    case JR:
        getToken(src,token);
        rs = regSearch(token);
        rd = 0;
        rt = 0;
        shamt = 0;
        break;
    case LB:
    case LBU:
    case LH:
    case LHU:
    case LW:
    case LWCL:
    case LWL:
    case LWR:
    case LL:
    case SB:
    case SH:
    case SW:
    case SWL:
    case SWR:
    case SC:{
        getToken(src,token);
        rt = regSearch(token);
        getToken(src,token);
        int wl = strlen(token);
        int i = 0;
        char num[6];
        while(token[i] != '('){
            num[i] = token[i];
            i++;
        }
        imm = atoi(num);
        strncpy(num,token+i+1,wl-i-2);
        num[wl-i-2] = '\0';
        rs = regSearch(num);
        break;
    }
    case MFHI:
    case MFLO:
        getToken(src,token);
        rd = regSearch(token);
        rs = 0;
        rt = 0;
        shamt = 0;
        break;
    case MTHI:
    case MTLO:
        getToken(src,token);
        rs = regSearch(token);
        rd = 0;
        rt = 0;
        shamt = 0;
        break;
    case SYSCALL:
        rs = 0;
        rt = 0;
        rd = 0;
        shamt = 0;
        break;
    default:
        perror("No matching instruction!");
        break;
    }
    FORMAT inst_fmt = inst_list[inst_num].format;
    op = inst_list[inst_num].op;
    func = inst_list[inst_num].func;
    if(inst_fmt == R){
        m_code = (op<<26) + (rs<<21) + (rt<<16) + (rd<<11) + (shamt<<6) + func;
    }else if(inst_fmt == FJ){
        m_code = (op<<26) + address;
    }else if (func == -1){
        m_code = (op<<26) + (rs<<21) + (rt<<16) + (unsigned short)imm;
    }else{
        m_code = (op<<26) + (rs<<21) + (func<<16) + (unsigned short)imm;
    }
    //printf("%s: ",inst_list[inst_num].name);
    return m_code;
}

