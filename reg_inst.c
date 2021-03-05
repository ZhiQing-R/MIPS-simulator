#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "reg_inst.h"


struct reg* reg_list;
struct inst* inst_list;
long* lo;
long* hi;

void regInit(){
    reg_list = malloc(32*sizeof(struct reg));
    strcpy(reg_list[0].name,"zero");
    strcpy(reg_list[1].name,"at");
    strcpy(reg_list[2].name,"v0");
    strcpy(reg_list[3].name,"v1");
    strcpy(reg_list[4].name,"a0");
    strcpy(reg_list[5].name,"a1");
    strcpy(reg_list[6].name,"a2");
    strcpy(reg_list[7].name,"a3");
    strcpy(reg_list[8].name,"t0");
    strcpy(reg_list[9].name,"t1");
    strcpy(reg_list[10].name,"t2");
    strcpy(reg_list[11].name,"t3");
    strcpy(reg_list[12].name,"t4");
    strcpy(reg_list[13].name,"t5");
    strcpy(reg_list[14].name,"t6");
    strcpy(reg_list[15].name,"t7");
    strcpy(reg_list[16].name,"s0");
    strcpy(reg_list[17].name,"s1");
    strcpy(reg_list[18].name,"s2");
    strcpy(reg_list[19].name,"s3");
    strcpy(reg_list[20].name,"s4");
    strcpy(reg_list[21].name,"s5");
    strcpy(reg_list[22].name,"s6");
    strcpy(reg_list[23].name,"s7");
    strcpy(reg_list[24].name,"t8");
    strcpy(reg_list[25].name,"t9");
    strcpy(reg_list[26].name,"k0");
    strcpy(reg_list[27].name,"k1");
    strcpy(reg_list[28].name,"gp");
    strcpy(reg_list[29].name,"sp");
    strcpy(reg_list[30].name,"fp");
    strcpy(reg_list[31].name,"ra");
}

void instInit(){
    inst_list = malloc(79*sizeof(struct inst));
    
    strcpy(inst_list[0].name,"add");
    inst_list[0].format = R;
    inst_list[0].op = 0;
    inst_list[0].func = 32;

    strcpy(inst_list[1].name,"addu");
    inst_list[1].format = R;
    inst_list[1].op = 0;
    inst_list[1].func = 33;

    strcpy(inst_list[2].name,"addi");
    inst_list[2].format = I;
    inst_list[2].op = 8;
    inst_list[2].func = -1;

    strcpy(inst_list[3].name,"addiu");
    inst_list[3].format = I;
    inst_list[3].op = 9;
    inst_list[3].func = -1;

    strcpy(inst_list[4].name,"and");
    inst_list[4].format = R;
    inst_list[4].op = 0;
    inst_list[4].func = 36;

    strcpy(inst_list[5].name,"andi");
    inst_list[5].format = I;
    inst_list[5].op = 12;
    inst_list[5].func = -1;

    strcpy(inst_list[6].name,"clo");
    inst_list[6].format = R;
    inst_list[6].op = 28;
    inst_list[6].func = 33;

    strcpy(inst_list[7].name,"clz");
    inst_list[7].format = R;
    inst_list[7].op = 28;
    inst_list[7].func = 32;

    strcpy(inst_list[8].name,"div");
    inst_list[8].format = R;
    inst_list[8].op = 0;
    inst_list[8].func = 26;

    strcpy(inst_list[9].name,"divu");
    inst_list[9].format = R;
    inst_list[9].op = 0;
    inst_list[9].func = 27;

    strcpy(inst_list[10].name,"mult");
    inst_list[10].format = R;
    inst_list[10].op = 0;
    inst_list[10].func = 24;

    strcpy(inst_list[11].name,"multu");
    inst_list[11].format = R;
    inst_list[11].op = 0;
    inst_list[11].func = 25;

    strcpy(inst_list[12].name,"mul");
    inst_list[12].format = R;
    inst_list[12].op = 28;
    inst_list[12].func = 2;

    strcpy(inst_list[13].name,"madd");
    inst_list[13].format = R;
    inst_list[13].op = 28;
    inst_list[13].func = 0;

    strcpy(inst_list[14].name,"msub");
    inst_list[14].format = R;
    inst_list[14].op = 28;
    inst_list[14].func = 1;

    strcpy(inst_list[15].name,"maddu");
    inst_list[15].format = R;
    inst_list[15].op = 28;
    inst_list[15].func = 4;

    strcpy(inst_list[16].name,"msubu");
    inst_list[16].format = R;
    inst_list[16].op = 28;
    inst_list[16].func = 5;

    strcpy(inst_list[17].name,"nor");
    inst_list[17].format = R;
    inst_list[17].op = 0;
    inst_list[17].func = 39;

    strcpy(inst_list[18].name,"or");
    inst_list[18].format = R;
    inst_list[18].op = 0;
    inst_list[18].func = 37;

    strcpy(inst_list[19].name,"ori");
    inst_list[19].format = I;
    inst_list[19].op = 13;
    inst_list[19].func = -1;

    strcpy(inst_list[20].name,"sll");
    inst_list[20].format = R;
    inst_list[20].op = 0;
    inst_list[20].func = 0;

    strcpy(inst_list[21].name,"sllv");
    inst_list[21].format = R;
    inst_list[21].op = 0;
    inst_list[21].func = 4;

    strcpy(inst_list[22].name,"sra");
    inst_list[22].format = R;
    inst_list[22].op = 0;
    inst_list[22].func = 3;

    strcpy(inst_list[23].name,"srav");
    inst_list[23].format = R;
    inst_list[23].op = 0;
    inst_list[23].func = 7;

    strcpy(inst_list[24].name,"srl");
    inst_list[24].format = R;
    inst_list[24].op = 0;
    inst_list[24].func = 2;

    strcpy(inst_list[25].name,"srlv");
    inst_list[25].format = R;
    inst_list[25].op = 0;
    inst_list[25].func = 6;

    strcpy(inst_list[26].name,"sub");
    inst_list[26].format = R;
    inst_list[26].op = 0;
    inst_list[26].func = 34;

    strcpy(inst_list[27].name,"subu");
    inst_list[27].format = R;
    inst_list[27].op = 0;
    inst_list[27].func = 35;

    strcpy(inst_list[28].name,"xor");
    inst_list[28].format = R;
    inst_list[28].op = 0;
    inst_list[28].func = 38;

    strcpy(inst_list[29].name,"xori");
    inst_list[29].format = I;
    inst_list[29].op = 14;
    inst_list[29].func = -1;

    strcpy(inst_list[30].name,"lui");
    inst_list[30].format = I;
    inst_list[30].op = 15;
    inst_list[30].func = -1;

    strcpy(inst_list[31].name,"slt");
    inst_list[31].format = R;
    inst_list[31].op = 0;
    inst_list[31].func = 42;

    strcpy(inst_list[32].name,"sltu");
    inst_list[32].format = R;
    inst_list[32].op = 0;
    inst_list[32].func = 43;

    strcpy(inst_list[33].name,"slti");
    inst_list[33].format = I;
    inst_list[33].op = 10;
    inst_list[33].func = -1;

    strcpy(inst_list[34].name,"sltiu");
    inst_list[34].format = I;
    inst_list[34].op = 11;
    inst_list[34].func = -1;

    strcpy(inst_list[35].name,"beq");
    inst_list[35].format = I;
    inst_list[35].op = 4;
    inst_list[35].func = -1;

    strcpy(inst_list[36].name,"bgez");
    inst_list[36].format = I;
    inst_list[36].op = 1;
    inst_list[36].func = 1;

    strcpy(inst_list[37].name,"bgezal");
    inst_list[37].format = I;
    inst_list[37].op = 1;
    inst_list[37].func = 0x11;

    strcpy(inst_list[38].name,"bgtz");
    inst_list[38].format = I;
    inst_list[38].op = 7;
    inst_list[38].func = 0;

    strcpy(inst_list[39].name,"blez");
    inst_list[39].format = I;
    inst_list[39].op = 6;
    inst_list[39].func = 0;

    strcpy(inst_list[40].name,"bltzal");
    inst_list[40].format = I;
    inst_list[40].op = 1;
    inst_list[40].func = 0x10;

    strcpy(inst_list[41].name,"bltz");
    inst_list[41].format = I;
    inst_list[41].op = 1;
    inst_list[41].func = 0;

    strcpy(inst_list[42].name,"bne");
    inst_list[42].format = I;
    inst_list[42].op = 5;
    inst_list[42].func = -1;

    strcpy(inst_list[43].name,"j");
    inst_list[43].format = FJ;
    inst_list[43].op = 2;
    inst_list[43].func = -1;

    strcpy(inst_list[44].name,"jal");
    inst_list[44].format = FJ;
    inst_list[44].op = 3;
    inst_list[44].func = -1;

    strcpy(inst_list[45].name,"jalr");
    inst_list[45].format = R;
    inst_list[45].op = 0;
    inst_list[45].func = 9;

    strcpy(inst_list[46].name,"jr");
    inst_list[46].format = R;
    inst_list[46].op = 0;
    inst_list[46].func = 8;

    strcpy(inst_list[47].name,"teq");
    inst_list[47].format = R;
    inst_list[47].op = 0;
    inst_list[47].func = 52;

    strcpy(inst_list[48].name,"teqi");
    inst_list[48].format = I;
    inst_list[48].op = 1;
    inst_list[48].func = 0xc;

    strcpy(inst_list[49].name,"tne");
    inst_list[49].format = R;
    inst_list[49].op = 0;
    inst_list[49].func = 54;

    strcpy(inst_list[50].name,"tnei");
    inst_list[50].format = I;
    inst_list[50].op = 1;
    inst_list[50].func = 0xe;

    strcpy(inst_list[51].name,"tge");
    inst_list[51].format = R;
    inst_list[51].op = 0;
    inst_list[51].func = 48;

    strcpy(inst_list[52].name,"tgeu");
    inst_list[52].format = R;
    inst_list[52].op = 0;
    inst_list[52].func = 49;

    strcpy(inst_list[53].name,"tgei");
    inst_list[53].format = I;
    inst_list[53].op = 1;
    inst_list[53].func = 8;

    strcpy(inst_list[54].name,"tgeiu");
    inst_list[54].format = I;
    inst_list[54].op = 1;
    inst_list[54].func = 9;

    strcpy(inst_list[55].name,"tlt");
    inst_list[55].format = R;
    inst_list[55].op = 0;
    inst_list[55].func = 50;

    strcpy(inst_list[56].name,"tltu");
    inst_list[56].format = R;
    inst_list[56].op = 0;
    inst_list[56].func = 51;

    strcpy(inst_list[57].name,"tlti");
    inst_list[57].format = I;
    inst_list[57].op = 1;
    inst_list[57].func = 10;

    strcpy(inst_list[58].name,"tltiu");
    inst_list[58].format = I;
    inst_list[58].op = 1;
    inst_list[58].func = 11;

    strcpy(inst_list[59].name,"lb");
    inst_list[59].format = I;
    inst_list[59].op = 32;
    inst_list[59].func = -1;

    strcpy(inst_list[60].name,"lbu");
    inst_list[60].format = I;
    inst_list[60].op = 36;
    inst_list[60].func = -1;

    strcpy(inst_list[61].name,"lh");
    inst_list[61].format = I;
    inst_list[61].op = 33;
    inst_list[61].func = -1;

    strcpy(inst_list[62].name,"lhu");
    inst_list[62].format = I;
    inst_list[62].op = 37;
    inst_list[62].func = -1;

    strcpy(inst_list[63].name,"lw");
    inst_list[63].format = I;
    inst_list[63].op = 35;
    inst_list[63].func = -1;

    strcpy(inst_list[64].name,"lwcl");
    inst_list[64].format = I;
    inst_list[64].op = 49;
    inst_list[64].func = -1;

    strcpy(inst_list[65].name,"lwl");
    inst_list[65].format = I;
    inst_list[65].op = 34;
    inst_list[65].func = -1;

    strcpy(inst_list[66].name,"lwr");
    inst_list[66].format = I;
    inst_list[66].op = 38;
    inst_list[66].func = -1;

    strcpy(inst_list[67].name,"ll");
    inst_list[67].format = I;
    inst_list[67].op = 48;
    inst_list[67].func = -1;

    strcpy(inst_list[68].name,"sb");
    inst_list[68].format = I;
    inst_list[68].op = 40;
    inst_list[68].func = -1;

    strcpy(inst_list[69].name,"sh");
    inst_list[69].format = I;
    inst_list[69].op = 41;
    inst_list[69].func = -1;

    strcpy(inst_list[70].name,"sw");
    inst_list[70].format = I;
    inst_list[70].op = 43;
    inst_list[70].func = -1;

    strcpy(inst_list[71].name,"swl");
    inst_list[71].format = I;
    inst_list[71].op = 42;
    inst_list[71].func = -1;

    strcpy(inst_list[72].name,"swr");
    inst_list[72].format = I;
    inst_list[72].op = 46;
    inst_list[72].func = -1;

    strcpy(inst_list[73].name,"sc");
    inst_list[73].format = I;
    inst_list[73].op = 56;
    inst_list[73].func = -1;

    strcpy(inst_list[74].name,"mfhi");
    inst_list[74].format = R;
    inst_list[74].op = 0;
    inst_list[74].func = 16;

    strcpy(inst_list[75].name,"mflo");
    inst_list[75].format = R;
    inst_list[75].op = 0;
    inst_list[75].func = 18;

    strcpy(inst_list[76].name,"mthi");
    inst_list[76].format = R;
    inst_list[76].op = 0;
    inst_list[76].func = 17;

    strcpy(inst_list[77].name,"mtlo");
    inst_list[77].format = R;
    inst_list[77].op = 0;
    inst_list[77].func = 19;

    strcpy(inst_list[78].name,"syscall");
    inst_list[78].format = R;
    inst_list[78].op = 0;
    inst_list[78].func = 12;
}

int regSearch(char* str){
    char reg_name[6] = {'$'};
    if(47<*str && *str<58){
        return atoi(str);
    }
    for(int i = 0; i < 32; i++){
        strcpy(reg_name+1,reg_list[i].name);
        if(strcmp(reg_name,str) == 0) return i;
    }
    return -1;
}

int instSearch(char* str){
    for(int i = 0; i < 79; i++){
        if(strcmp(inst_list[i].name,str) == 0) return i;
    }
    return -1;
}
