#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "reg_inst.h"

int* lo;
int* hi;
extern int* PC;
extern long realm;
extern int llbit;
extern FILE* syscall_inputs;
extern FILE* output_file;
extern FILE* input_mips;

void add(reg* rs, reg* rt, reg* rd){
    int result = rs->val+ rt->val;
    if(rs->val > 0 && rt->val > 0 && result < 0){
        puts("Addition overflow!");
    }else if(rs->val < 0 && rt->val < 0 && result > 0){
        puts("Addition overflow!");
    }else{
        rd->val = result;
    }
    
}

void addu(reg* rs, reg* rt, reg* rd){
    rd->val = rs->val + rt->val;
}

void addi(reg* rt, reg* rs, short imm){
    int result = imm + rs->val;
    if(rs->val > 0 && imm > 0 && result < 0){
        puts("Addition overflow!");
    }else if(rs->val < 0 && imm < 0 && result > 0){
        puts("Addition overflow!");
    }else{
        rt->val = result;
    }
}

void addiu(reg* rt, reg* rs, short imm){
    rt->val = imm + rs->val;
}

void and(reg* rs, reg* rt, reg* rd){
    rd->val = rs->val & rt->val;
}

void andi(reg* rt, reg* rs, short imm){
    rt->val = imm & rs->val;
}

void clz(reg* rd, reg* rs){
    if(rs->val < 0){
        rd->val = 0;
        return;
    }
    int cnt = 1;
    int val = rs->val;
    while(cnt<32){
        if(val>>(31-cnt)%2 == 0){
            cnt++;
        }else{
            break;
        }
    }
    rd->val = cnt;
}

void clo(reg* rd, reg* rs){
    if(rs->val >= 0){
        rd->val = 0;
        return;
    }
    int cnt = 1;
    int val = rs->val;
    while(cnt<32){
        if(val>>(31-cnt)%2 == 1){
            cnt++;
        }else{
            break;
        }
    }
    rd->val = cnt;
}

void _div(reg* rs, reg* rt){
    if(rt->val == 0){
        puts("Zero division!");
    }
    *lo = rs->val/rt->val;
    *hi = rs->val%rt->val;
}

void divu(reg* rs, reg* rt){
    if(rt->val == 0){
        puts("Zero division!");
    }
    unsigned int a = rs->val;
    unsigned int b = rt->val;
    *lo = a/b;
    *hi = a%b;
}

void mult(reg* rs, reg* rt){
    long result = rs->val * rt->val;
    int low = result;
    int high = result>>32;
    *lo = low;
    *hi = high;
}

void multu(reg* rs, reg* rt){
    unsigned int a = rs->val;
    unsigned int b = rt->val;
    unsigned long result = a * b;
    unsigned int low = result;
    unsigned int high = result>>32;
    *lo = low;
    *hi = high;
}

void mul(reg* rd, reg* rs, reg* rt){
    long result = rs->val * rt->val;
    rd->val = result;
}

void madd(reg* rs, reg* rt){
    long result = rs->val * rt->val;
    int low = result;
    int high = result>>32;
    *lo = *lo + low;
    *hi = *hi + high;
}

void maddu(reg* rs, reg* rt){
    long result = (unsigned int)rs->val * (unsigned int)rt->val;
    int low = result;
    int high = result>>32;
    *lo = *lo + low;
    *hi = *hi + high;
}

void msub(reg* rs, reg* rt){
    long result = rs->val * rt->val;
    int low = result;
    int high = result>>32;
    *lo = *lo - low;
    *hi = *hi - high;
}

void msubu(reg* rs, reg* rt){
    unsigned int a = rs->val;
    unsigned int b = rt->val;
    unsigned long result = a * b;
    unsigned int low = result;
    unsigned int high = result>>32;
    *lo = *lo - low;
    *hi = *hi - high;
}

void nor(reg* rd, reg* rs, reg* rt){
    rd->val = !(rs->val | rt->val);
}

void or(reg* rd, reg* rs, reg* rt){
    rd->val = rs->val | rt->val;
}

void ori(reg* rt, reg* rs, short imm){
    rt->val = rs->val | imm;
}

void sll(reg* rd, reg* rt, int shamt){
    rd->val = rt->val << shamt;
}

void sllv(reg* rd, reg* rt, reg* rs){
    rd->val = rt->val << rs->val;
}

void sra(reg* rd, reg* rt, int shamt){
    rd->val = rt->val >> shamt;
}

void srav(reg* rd, reg* rt, reg* rs){
    rd->val = rt->val >> rs->val;
}

void srl(reg* rd, reg* rt, int shamt){
    unsigned int tmp = rt->val;
    tmp = tmp >> shamt;
    rd->val = tmp;
}

void srlv(reg* rd, reg* rt, reg* rs){
    unsigned int tmp = rt->val;
    tmp = tmp >> rs->val;
    rd->val = tmp;
}

void sub(reg* rd, reg* rs, reg* rt){
    int negRt = 0-rt->val;
    int result = negRt + rs->val;
    if(rs->val > 0 && negRt > 0 && result < 0){
        puts("subtraction overflow");
    }else if(rs->val < 0 && negRt < 0 && result > 0){
        puts("subtraction overflow");
    }else{
        rd->val = result;
    }
}

void subu(reg* rd, reg* rs, reg* rt){
    unsigned int RS = rs->val;
    unsigned int RT = rt->val;
    unsigned int result = RS - RT;
    rd->val = result;
}

void xor(reg* rd, reg* rs, reg* rt){
    rd->val = rs->val ^ rt->val;
}

void xori(reg* rt, reg* rs, short imm){
    rt->val = rs->val ^ imm;
}

void lui(reg* rt, short imm){
    int result = imm;
    rt->val = result << 16;
}

void slt(reg* rd, reg* rs, reg* rt){
    if(rs->val < rt->val){
        rd->val = 1;
    }else{
        rd->val = 0;
    }
}

void sltu(reg* rd, reg* rs, reg* rt){
    unsigned int RS = rs->val;
    unsigned int RT = rt->val;
    if(RS < RT){
        rd->val = 1;
    }else{
        rd->val = 0;
    }
}

void slti(reg* rt, reg* rs, short imm){
    if(rs->val < imm){
        rt->val = 1;
    }else{
        rt->val = 0;
    }
}

void sltiu(reg* rt, reg* rs, short imm){
    unsigned int RS = rs->val;
    unsigned int IMM = (unsigned short)imm;
    if(rs->val < IMM){
        rt->val = 1;
    }else{
        rt->val = 0;
    }
}

void beq(reg* rs, reg* rt, short imm){
    if(rs->val == rt->val){
        PC = PC + imm;
    }
}

void bgez(reg* rs, short imm){
    if(rs->val >= 0){
        PC = PC + imm;
    }
}

void bgezal(reg* rs, short imm){
    reg_list[30].val = (long)PC - realm + 4;
    if(rs->val >= 0){
        PC = PC + imm;
    }
}

void bgtz(reg* rs, short imm){
    if(rs->val > 0){
        PC = PC + imm;
    }
}

void blez(reg* rs, short imm){
    if(rs->val <= 0){
        PC = PC + imm;
    }
}

void bltzal(reg* rs, short imm){
    reg_list[30].val = (long)PC - realm + 4;
    if(rs->val < 0){
        PC = PC + imm;
    }
}

void bltz(reg* rs, short imm){
    if(rs->val < 0){
        PC = PC + imm;
    }
}

void bne(reg* rs, reg* rt, short imm){
    if(rs->val != rt->val){
        PC = PC + imm;
    }
}

void j(int address){
    int relative_addr = (long)PC - realm;
    int true_addr = (relative_addr & 0xF0000000) + ((address << 2) & 0x0FFFFFFF);
    PC = (int*)(true_addr + realm);
}

void jal(int address){
    int relative_addr = (long)PC - realm;
    reg_list[31].val = relative_addr + 4;
    int true_addr = (relative_addr & 0xF0000000) + ((address << 2) & 0x0FFFFFFF);
    PC = (int*)(true_addr + realm);
}

void jalr(reg* rs, reg* rd){
    int relative_addr = (long)PC - realm;
    rd->val = relative_addr + 4;
    PC = (int*)(rs->val + realm);
}

void jr(reg* rs){
    PC = (int*)(rs->val + realm);
}

void teq(reg* rs, reg* rt){
    if(rs->val == rt->val){
        puts("TEQ Trap");
    }
}

void teqi(reg* rs, short imm){
    if(rs->val == imm){
        puts("TEQI Trap");
    }
}

void tne(reg* rs, reg* rt){
    if(rs->val != rt->val){
        puts("TNE Trap");
    }
}

void tnei(reg* rs, short imm){
    if(rs->val != imm){
        puts("TNEI Trap");
    }
}

void tge(reg* rs, reg* rt){
    if(rs->val >= rt->val){
        puts("TGE Trap");
    }
}

void tgeu(reg* rs, reg* rt){
    unsigned int RS = rs->val;
    unsigned int RT = rt->val;
    if(RS >= RT){
        puts("TGEU Trap");
    }
}

void tgei(reg* rs, short imm){
    if(rs->val >= imm){
        puts("TGEI Trap");
    }
}

void tgeiu(reg* rs, short imm){
    int IMM = imm;
    if(rs->val >= (unsigned int)IMM){
        puts("TGEIU Trap");
    }
}

void tlt(reg* rs, reg* rt){
    if(rs->val < rt->val){
        puts("TLT Trap");
    }
}

void tltu(reg* rs, reg* rt){
    unsigned int RS = rs->val;
    unsigned int RT = rt->val;
    if(RS < RT){
        puts("TLTU Trap");
    }
}

void tlti(reg* rs, short imm){
    if(rs->val < imm){
        puts("TLTI Trap");
    }
}

void tltiu(reg* rs, short imm){
    int IMM = imm;
    if(rs->val < (unsigned int)IMM){
        puts("TLTIU Trap");
    }
}

void lb(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = (int*)(realm + trueAddr);
    rt->val = *ptr & 0x000000FF;
}

void lbu(reg* rs, reg* rt, int address){
    address = 0x0000FFFF & address;
    int trueAddr = rs->val + address;
    int* ptr = (int*)(realm + trueAddr);
    rt->val = *ptr & 0x000000FF;
}

void lh(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = (int*)(realm + trueAddr);
    rt->val = *ptr & 0x0000FFFF;
}

void lhu(reg* rs, reg* rt, int address){
    address = 0x0000FFFF & address;
    int trueAddr = rs->val + address;
    int* ptr = (int*)(realm + trueAddr);
    rt->val = *ptr & 0x0000FFFF;
}

void lw(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = (int*)(realm + trueAddr);
    rt->val = *ptr;
}

void lwl(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int effAddr = (trueAddr & 0xFFFFFFFC) + 3;
    int byteNum = effAddr - trueAddr;
    int* wordPtr = (int*)(realm + effAddr - 3);
    int word = *wordPtr;
    switch(byteNum){
        case 0:
            word = (word & 0x000000FF)<<24;
            rt->val = rt->val & 0x00FFFFFF;
            break;
        case 1:
            word = (word & 0x0000FFFF)<<16;
            rt->val = rt->val & 0x0000FFFF;
            break;
        case 2:
            word = (word & 0x00FFFFFF)<<8;
            rt->val = rt->val & 0x000000FF;
            break;
        case 3:
            rt->val = 0;
            break;
        default:
            break;
    }
    rt->val = rt->val + word;
}

void lwr(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int effAddr = trueAddr & 0xFFFFFFFC;
    int byteNum = trueAddr - effAddr;
    int* wordPtr = (int*)(realm + effAddr);
    unsigned int word = *wordPtr;
    switch(byteNum){
        case 0:
            word = (word & 0xFF000000)>>24;
            rt->val = rt->val & 0xFFFFFF00;
            break;
        case 1:
            word = (word & 0xFFFF0000)>>16;
            rt->val = rt->val & 0xFFFF0000;
            break;
        case 2:
            word = (word & 0xFFFFFF00)<<8;
            rt->val = rt->val & 0xFF000000;
            break;
        case 3:
            rt->val = 0;
            break;
        default:
            break;
    }
    rt->val = rt->val + word;
}

void ll(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = (int*)(realm + trueAddr);
    rt->val = *ptr;
    llbit = 1;
}

void sb(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = (int*)(realm + trueAddr);
    *ptr = rt->val & 0x000000FF;
}

void sh(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = (int*)(realm + trueAddr);
    *ptr = rt->val & 0x0000FFFF;
}

void sw(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = (int*)(realm + trueAddr);
    *ptr = rt->val;
}

void swl(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int effAddr = (trueAddr & 0xFFFFFFFC) + 3;
    int byteNum = effAddr - trueAddr;
    int* wordPtr = (int*)(realm + effAddr - 3);
    int word = *wordPtr;
    unsigned int bytesToStore = rt->val;
    switch(byteNum){
        case 0:
            word = word & 0xFFFFFF00;
            bytesToStore = (bytesToStore & 0xFF000000) >> 24;
            break;
        case 1:
            word = word & 0xFFFF0000;
            bytesToStore = (bytesToStore & 0xFFFF0000) >> 16;
            break;
        case 2:
            word = word & 0xFF000000;
            bytesToStore = (bytesToStore & 0xFFFFFF00) >> 8;
            break;
        case 3:
            word = 0;
            break;
        default:
            break;
    }
    word = word + bytesToStore;
    *wordPtr = word;
}

void swr(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int effAddr = (trueAddr & 0xFFFFFFFC) + 3;
    int byteNum = effAddr - trueAddr;
    int* wordPtr = (int*)(realm + effAddr - 3);
    int word = *wordPtr;
    unsigned int bytesToStore = rt->val;
    switch(byteNum){
        case 0:
            word = word & 0x00FFFFFF;
            bytesToStore = (bytesToStore & 0x000000FF) << 24;
            break;
        case 1:
            word = word & 0x0000FFFF;
            bytesToStore = (bytesToStore & 0x0000FFFF) << 16;
            break;
        case 2:
            word = word & 0x000000FF;
            bytesToStore = (bytesToStore & 0x00FFFFFF) << 8;
            break;
        case 3:
            word = 0;
            break;
        default:
            break;
    }
    word = word + bytesToStore;
    *wordPtr = word;
}

void sc(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = (int*)(realm + trueAddr);
    if(llbit){
        *ptr = rt->val;
        rt->val = 1;
    }else{
        rt->val = 0;
    }
}

void mfhi(reg* rd){
    rd->val = *hi;
}

void mflo(reg* rd){
    rd->val = *lo;
}

void mthi(reg* rs){
    *hi = rs->val;
}

void mtlo(reg* rs){
    *lo = rs->val;
}

void _syscall(){
    int flag = reg_list[2].val;
    switch(flag){
        case 1:
            fprintf(output_file,"%d",reg_list[4].val);
            break;
        case 4:{
            char* str = (char*)(realm + reg_list[4].val);
            fprintf(output_file,"%s",str);
            break;
        }
        case 5:{
            char input[128];
            char pivot;
            for(int i = 0; i < 128; i++){
                if((pivot = getc(syscall_inputs)) != '\n'){
                    input[i] = pivot;
                }else{
                    input[i] = '\0';
                    break;
                }
            }
            if(input[0] == '0' && (input[1] == 'x' || input[1] == 'X')){
                reg_list[2].val = strtol(input,NULL,16);
            }else{
                reg_list[2].val = atoi(input);
            }
            break;
        }
        case 8:{
            int len = reg_list[5].val;
            char input[len];
            char pivot;
            for(int i = 0; i < len; i++){
                if((pivot = getc(syscall_inputs)) != '\n'){
                    input[i] = pivot;
                }else{
                    input[i] = '\0';
                    break;
                }
            }
            strcpy((char*)(reg_list[4].val + realm),input);
            break;
        }
        case 9:{
            reg_list[2].val = reg_list[28].val + reg_list[4].val;
            break;
        }
        case 10:
            exit(0);
            break;
        case 11:
            fprintf(output_file,"%c",reg_list[4].val);
            break;
        case 12:
            reg_list[2].val = getc(syscall_inputs);
            break;
        case 13:
            reg_list[2].val = open((char*)(reg_list[4].val + realm),reg_list[5].val,reg_list[6].val);
            break;
        case 14:
            reg_list[2].val = read(reg_list[4].val,(void*)(reg_list[5].val + realm),reg_list[6].val);
            break;
        case 15:
            reg_list[2].val = write(reg_list[4].val,(void*)(reg_list[5].val + realm),reg_list[6].val);
            break;
        case 16:
            close(reg_list[4].val);
            break;
        case 17:
            exit(reg_list[4].val);
            break;
        default:
            break;
    }
}
