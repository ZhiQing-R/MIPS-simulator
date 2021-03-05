#ifndef REGISTER_H
#define REGISTER_H

#include <string.h>

enum INSTRUCTION{
    ADD = 0,
    ADDU,
    ADDI,
    ADDIU,
    AND,
    ANDI,
    CLO,
    CLZ,
    DIV,
    DIVU,
    MULT,
    MULTU,
    MUL,
    MADD,
    MSUB,
    MADDU,
    MSUBU,
    NOR,
    OR,
    ORI,
    SLL,
    SLLV,
    SRA,
    SRAV,
    SRL,
    SRLV,
    SUB,
    SUBU,
    XOR,
    XORI,
    LUI,
    SLT,
    SLTU,
    SLTI,
    SLTIU,
    BEQ,
    BGEZ,
    BGEZAL,
    BGTZ,
    BLEZ,
    BLTZAL,
    BLTZ,
    BNE,
    J,
    JAL,
    JALR,
    JR,
    TEQ,
    TEQI,
    TNE,
    TNEI,
    TGE,
    TGEU,
    TGEI,
    TGEIU,
    TLT,
    TLTU,
    TLTI,
    TLTIU,
    LB,
    LBU,
    LH,
    LHU,
    LW,
    LWCL,
    LWL,
    LWR,
    LL,
    SB,
    SH,
    SW,
    SWL,
    SWR,
    SC,
    MFHI,
    MFLO,
    MTHI,
    MTLO,
    SYSCALL
};

typedef enum FORMAT{
    R = 0,
    I,
    FJ
}FORMAT;

typedef struct reg{
    char name[5];
    int val;
}reg;

typedef struct inst{
    FORMAT format;
    char name[8];
    int op;
    int func;
}inst;

extern reg* reg_list;
extern inst* inst_list;
extern long* lo;
extern long* hi;

void regInit();
void instInit();
int regSearch(char* str);
int instSearch(char* str);

#endif