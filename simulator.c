#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freader.h"
#include "reg_inst.h"

int* PC;
long realm;
int llbit = 0;
FILE* syscall_inputs;
FILE* output_file;
FILE* input_mips;

void execute(){
    int instruction = *PC;
    int jump = 0;
    int op = (unsigned int)instruction >> 26;
    FORMAT type;
    reg* rs, *rd, *rt;
    int func, address, shamt;
    short imm;
    for(int i = 0; i < 79; i++){
        if(inst_list[i].op == op){
            type = inst_list[i].format;
            break;
        }
    }
    if(type == R){
        func = instruction & 0x0000003F;
        rs = &reg_list[(instruction & 0x03e00000)>>21];
        rt = &reg_list[(instruction & 0x001f0000)>>16];
        rd = &reg_list[(instruction & 0x0000f800)>>11];
        shamt = (instruction & 0x000007c0) >> 6;
        /*for(int i = 0; i < 79; i++){
            if(inst_list[i].op == op && inst_list[i].func == func){
                printf("%s %s %s %s %d\n",inst_list[i].name,rd->name,rs->name,rt->name,shamt);
                break;
            }
        }*/
    }else if(type == FJ){
        address = instruction & 0x03FFFFFF;
        //printf("Jal %x\n",address);
    }else{
        rs = &reg_list[(instruction & 0x03e00000)>>21];
        rt = &reg_list[(instruction & 0x001f0000)>>16];
        imm = instruction & 0x0000FFFF;
        /*for(int i = 0; i < 79; i++){
            if(inst_list[i].op == op && (inst_list[i].func == -1 || inst_list[i].func == (instruction & 0x001f0000)>>16)){
                printf("%s %s %s %d\n",inst_list[i].name,rt->name,rs->name,imm);
                break;
            }
        }*/
    }
    switch(op){
        case 0:{
            switch(func){
                case 32:
                    add(rs,rt,rd);
                    break;
                case 33:
                    addu(rs,rt,rd);
                    break;
                case 36:
                    and(rs,rt,rd);
                    break;
                case 26:
                    _div(rs,rt);
                    break;
                case 27:
                    divu(rs,rt);
                    break;
                case 24:
                    mult(rs,rt);
                    break;
                case 25:
                    multu(rs,rt);
                    break;
                case 39:
                    nor(rd,rs,rt);
                    break;
                case 37:
                    or(rd,rs,rt);
                    break;
                case 0:
                    sll(rd,rt,shamt);
                    break;
                case 4:
                    sllv(rd,rt,rs);
                    break;
                case 3:
                    sra(rd,rt,shamt);
                    break;
                case 7:
                    srav(rd,rs,rt);
                    break;
                case 2:
                    srl(rd,rt,shamt);
                    break;
                case 6:
                    srlv(rd,rt,rs);
                    break;
                case 34:
                    sub(rd,rs,rt);
                    break;
                case 35:
                    subu(rd,rs,rt);
                    break;
                case 38:
                    xor(rd,rs,rt);
                    break;
                case 42:
                    slt(rd,rs,rt);
                    break;
                case 43:
                    sltu(rd,rs,rt);
                    break;
                case 9:
                    jalr(rs,rd);
                    jump = 1;
                    break;
                case 8:
                    jr(rs);
                    jump = 1;
                    break;
                case 52:
                    teq(rs,rt);
                    break;
                case 54:
                    tne(rs,rt);
                    break;
                case 48:
                    tge(rs,rt);
                    break;
                case 49:
                    tgeu(rs,rt);
                    break;
                case 50:
                    tlt(rs,rt);
                    break;
                case 51:
                    tltu(rs,rt);
                    break;
                case 16:
                    mfhi(rd);
                    break;
                case 18:
                    mflo(rd);
                    break;
                case 17:
                    mthi(rs);
                    break;
                case 19:
                    mtlo(rs);
                    break;
                case 12:
                    _syscall();
                    break;
                default:
                    puts("func not supported");
                    break;
            }
            break;
        }
        case 1:{
            switch((instruction && 0x001f0000)>>16){
                case 0:
                    bltz(rs,imm);
                    break;
                case 1:
                    bgez(rs,imm);
                    break;
                case 8:
                    tgei(rs,imm);
                    break;
                case 9:
                    tgeiu(rs,imm);
                    break;
                case 10:
                    tlti(rs,imm);
                    break;
                case 11:
                    tltiu(rs,imm);
                    break;
                case 14:
                    tnei(rs,imm);
                    break;
                case 16:
                    bltzal(rs,imm);
                    break;
                case 17:
                    bgezal(rs,imm);
                    break;
                default:
                    puts("Not supported");
                    break;
            }
            break;
        }
        case 2:
            j(address);
            jump = 1;
            break;
        case 3:
            jal(address);
            jump = 1;
            break;
        case 4:
            beq(rs,rt,imm);
            break;
        case 5:
            bne(rs,rt,imm);
            break;
        case 6:
            blez(rs,imm);
            break;
        case 7:
            bgtz(rs,imm);
            break;
        case 8:
            addi(rt,rs,imm);
            break;
        case 9:
            addiu(rt,rs,imm);
            break;
        case 10:
            slti(rt,rs,imm);
            break;
        case 11:
            sltiu(rt,rs,imm);
            break;
        case 12:
            andi(rt,rs,imm);
            break;
        case 13:
            ori(rt,rs,imm);
            break;
        case 14:
            xori(rt,rs,imm);
            break;
        case 15:
            lui(rt,imm);
            break;
        case 28:{
            switch(func){
                case 0:
                    madd(rs,rt);
                    break;
                case 1:
                    maddu(rs,rt);
                    break;
                case 2:
                    mul(rd,rs,rt);
                    break;
                case 4:
                    msub(rs,rt);
                    break;
                case 5:
                    msubu(rs,rt);
                    break;
                case 32:
                    clz(rd,rs);
                    break;
                case 33:
                    clo(rd,rs);
                    break;
                default:
                    puts("Not supported");
                    break;
            }
        }
        case 32:
            lb(rs,rt,imm);
            break;
        case 33:
            lh(rs,rt,imm);
            break;
        case 34:
            lwl(rs,rt,imm);
            break;
        case 35:
            lw(rs,rt,imm);
            break;
        case 36:
            lbu(rs,rt,imm);
            break;
        case 37:
            lhu(rs,rt,imm);
            break;
        case 38:
            lwr(rs,rt,imm);
            break;
        case 40:
            sb(rs,rt,imm);
            break;
        case 41:
            sh(rs,rt,imm);
            break;
        case 42:
            swl(rs,rt,imm);
            break;
        case 43:
            sw(rs,rt,imm);
            break;
        case 46:
            swr(rs,rt,imm);
            break;
        case 48:
            ll(rs,rt,imm);
            break;
        case 56:
            sc(rs,rt,imm);
            break;
        default:
            puts("Not supported");
            break;   
    }
    if(!jump){
        PC = PC + 1;
    }
}

int main(int argc, char** argv){
    if(argc < 4){
        printf("wrong number of arguments");
    }

    input_mips = fopen(argv[1], "r");
    //input_mips = fopen("code.asm","r");
    syscall_inputs = fopen(argv[2], "r");
    //syscall_inputs = stdin;
    output_file = fopen(argv[3], "w");
    //output_file = stdout;

    int* realmPtr = malloc(6*1024*1024);
    realm = (long)realmPtr;
    int* text_end = assemble(realm+0x400000,input_mips);
    rewind(input_mips);
    writeData(input_mips,realm + 0x500000);
    reg_list[29].val = 6*1024*1024 - 4;
    PC = (int*)(realm + 0x400000);
    while(PC < text_end){
        execute();
    }
    fclose(input_mips);
    fclose(output_file);
    fclose(syscall_inputs);
    return 0; 
}