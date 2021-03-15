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


void regInit();
void instInit();
int regSearch(char* str);
int instSearch(char* str);

void add(reg* rs, reg* rt, reg* rd);
void addu(reg* rs, reg* rt, reg* rd);
void addi(reg* rt, reg* rs, short imm);
void addiu(reg* rt, reg* rs, short imm);
void and(reg* rs, reg* rt, reg* rd);
void andi(reg* rt, reg* rs, short imm);
void clz(reg* rd, reg* rs);
void clo(reg* rd, reg* rs);
void _div(reg* rs, reg* rt);
void divu(reg* rs, reg* rt);
void mult(reg* rs, reg* rt);
void multu(reg* rs, reg* rt);
void mul(reg* rd, reg* rs, reg* rt);
void madd(reg* rs, reg* rt);
void maddu(reg* rs, reg* rt);
void msub(reg* rs, reg* rt);
void msubu(reg* rs, reg* rt);
void nor(reg* rd, reg* rs, reg* rt);
void or(reg* rd, reg* rs, reg* rt);
void ori(reg* rt, reg* rs, short imm);
void sll(reg* rd, reg* rt, int shamt);
void sllv(reg* rd, reg* rt, reg* rs);
void sra(reg* rd, reg* rt, int shamt);
void srav(reg* rd, reg* rt, reg* rs);
void srl(reg* rd, reg* rt, int shamt);
void srlv(reg* rd, reg* rt, reg* rs);
void sub(reg* rd, reg* rs, reg* rt);
void subu(reg* rd, reg* rs, reg* rt);
void xor(reg* rd, reg* rs, reg* rt);
void xori(reg* rt, reg* rs, short imm);
void lui(reg* rt, short imm);
void slt(reg* rd, reg* rs, reg* rt);
void sltu(reg* rd, reg* rs, reg* rt);
void slti(reg* rt, reg* rs, short imm);
void sltiu(reg* rt, reg* rs, short imm);
void beq(reg* rs, reg* rt, short imm);
void bgez(reg* rs, short imm);
void bgezal(reg* rs, short imm);
void bgtz(reg* rs, short imm);
void blez(reg* rs, short imm);
void bltzal(reg* rs, short imm);
void bltz(reg* rs, short imm);
void bne(reg* rs, reg* rt, short imm);
void j(int address);
void jal(int address);
void jalr(reg* rs, reg* rd);
void jr(reg* rs);
void teq(reg* rs, reg* rt);
void teqi(reg* rs, short imm);
void tne(reg* rs, reg* rt);
void tnei(reg* rs, short imm);
void tge(reg* rs, reg* rt);
void tgeu(reg* rs, reg* rt);
void tgei(reg* rs, short imm);
void tgeiu(reg* rs, short imm);
void tlt(reg* rs, reg* rt);
void tltu(reg* rs, reg* rt);
void tlti(reg* rs, short imm);
void tltiu(reg* rs, short imm);
void lb(reg* rs, reg* rt, int address);
void lbu(reg* rs, reg* rt, int address);
void lh(reg* rs, reg* rt, int address);
void lhu(reg* rs, reg* rt, int address);
void lw(reg* rs, reg* rt, int address);
void lwl(reg* rs, reg* rt, int address);
void lwr(reg* rs, reg* rt, int address);
void ll(reg* rs, reg* rt, int address);
void sb(reg* rs, reg* rt, int address);
void sh(reg* rs, reg* rt, int address);
void sw(reg* rs, reg* rt, int address);
void swl(reg* rs, reg* rt, int address);
void swr(reg* rs, reg* rt, int address);
void sc(reg* rs, reg* rt, int address);
void mfhi(reg* rd);
void mflo(reg* rd);
void mthi(reg* rs);
void mtlo(reg* rs);
void _syscall();
#endif