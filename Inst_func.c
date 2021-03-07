#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reg_inst.h"

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

void addi(reg* rt, reg* rs, int imm){
    int result = imm + rs->val;
    if(rs->val > 0 && imm > 0 && result < 0){
        puts("Addition overflow!");
    }else if(rs->val < 0 && imm < 0 && result > 0){
        puts("Addition overflow!");
    }else{
        rt->val = result;
    }
}

void addiu(reg* rt, reg* rs, int imm){
    rt->val = imm + rs->val;
}

void and(reg* rs, reg* rt, reg* rd){
    rd->val = rs->val & rt->val;
}

void andi(reg* rt, reg* rs, int imm){
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

void div(reg* rs, reg* rt){
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

void multu(reg* rs, reg* rt){
    unsigned int a = rs->val;
    unsigned int b = rt->val;
    unsigned long result = a * b;
    unsigned int low = result;
    unsigned int high = result>>32;
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

void ori(reg* rt, reg* rs, int imm){
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

void xori(reg* rt, reg* rs, int imm){
    rt->val = rs->val ^ imm;
}

void lui(reg* rt, int imm){
    rt->val = imm << 16;
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

void slti(reg* rt, reg* rs, int imm){
    imm = (imm << 16) >> 16;
    if(rs->val < imm){
        rt->val = 1;
    }else{
        rt->val = 0;
    }
}

void sltiu(reg* rt, reg* rs, int imm){
    unsigned int RS = rs->val;
    unsigned int IMM = (imm << 16) >> 16;
    if(rs->val < imm){
        rt->val = 1;
    }else{
        rt->val = 0;
    }
}

void beq(reg* rs, reg* rt, int imm){
    if(rs->val == rt->val){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void bgez(reg* rs, int imm){
    if(rs->val >= 0){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void bgezal(reg* rs, int imm){
    reg_list[30].val = PC - realm + 4;
    if(rs->val >= 0){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void bgtz(reg* rs, int imm){
    if(rs->val > 0){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void blez(reg* rs, int imm){
    if(rs->val <= 0){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void bltzal(reg* rs, int imm){
    reg_list[30].val = PC - realm + 4;
    if(rs->val < 0){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void bltz(reg* rs, int imm){
    if(rs->val < 0){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void bne(reg* rs, reg* rt, int imm){
    if(rs->val != rt->val){
        imm = (imm << 16) >> 16;
        PC = PC + imm;
    }
}

void j(int address){
    int relative_addr = PC - realm;
    int true_addr = (relative_addr & 0xF0000000) + ((address << 2) & 0x0FFFFFFF);
    PC = true_addr + realm;
}

void jal(int address){
    int relative_addr = PC - realm;
    reg_list[31].val = relative_addr + 4;
    int true_addr = (relative_addr & 0xF0000000) + ((address << 2) & 0x0FFFFFFF);
    PC = true_addr + realm;
}

void jalr(reg* rs, reg* rd){
    int relative_addr = PC - realm;
    rd->val = relative_addr + 4;
    PC = rs->val + realm;
}

void jr(reg* rs){
    PC = rs->val + realm;
}

void teq(reg* rs, reg* rt){
    if(rs->val == rt->val){
        puts("TEQ Trap");
    }
}

void teqi(reg* rs, int imm){
    imm = (imm << 16) >> 16;
    if(rs->val == imm){
        puts("TEQI Trap");
    }
}

void tne(reg* rs, reg* rt){
    if(rs->val != rt->val){
        puts("TNE Trap");
    }
}

void tnei(reg* rs, int imm){
    imm = (imm << 16) >> 16;
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

void tgei(reg* rs, int imm){
    imm = (imm << 16) >> 16;
    if(rs->val >= imm){
        puts("TGEI Trap");
    }
}

void tgeiu(reg* rs, int imm){
    unsigned int IMM = (imm << 16) >> 16;
    if(rs->val >= IMM){
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

void tlti(reg* rs, int imm){
    imm = (imm << 16) >> 16;
    if(rs->val < imm){
        puts("TLTI Trap");
    }
}

void tltiu(reg* rs, int imm){
    unsigned int IMM = (imm << 16) >> 16;
    if(rs->val < IMM){
        puts("TLTIU Trap");
    }
}

void lb(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = realm + trueAddr;
    rt->val = *ptr & 0x000000FF;
}

void lbu(reg* rs, reg* rt, int address){
    address = 0x0000FFFF & address;
    int trueAddr = rs->val + address;
    int* ptr = realm + trueAddr;
    rt->val = *ptr & 0x000000FF;
}

void lh(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = realm + trueAddr;
    rt->val = *ptr & 0x0000FFFF;
}

void lhu(reg* rs, reg* rt, int address){
    address = 0x0000FFFF & address;
    int trueAddr = rs->val + address;
    int* ptr = realm + trueAddr;
    rt->val = *ptr & 0x0000FFFF;
}

void lw(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int* ptr = realm + trueAddr;
    rt->val = *ptr;
}

void lwu(reg* rs, reg* rt, int address){
    address = 0x0000FFFF & address;
    int trueAddr = rs->val + address;
    int* ptr = realm + trueAddr;
    rt->val = *ptr;
}

void lwl(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int effAddr = (trueAddr & 0xFFFFFFFC) + 3;
    int byteNum = effAddr - trueAddr;
    int* wordPtr = realm + effAddr - 3;
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
    int* wordPtr = realm + effAddr;
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
    int* ptr = realm + trueAddr;
    rt->val = *ptr;
    llbit = 1;
}

void sb(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = realm + trueAddr;
    *ptr = rt->val & 0x000000FF;
}

void sh(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = realm + trueAddr;
    *ptr = rt->val & 0x0000FFFF;
}

void sw(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = address + rs->val;
    int* ptr = realm + trueAddr;
    *ptr = rt->val;
}

void swl(reg* rs, reg* rt, int address){
    address = (address << 16) >> 16;
    int trueAddr = rs->val + address;
    int effAddr = (trueAddr & 0xFFFFFFFC) + 3;
    int byteNum = effAddr - trueAddr;
    int* wordPtr = realm + effAddr - 3;
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
    int* wordPtr = realm + effAddr - 3;
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
    int* ptr = realm + trueAddr;
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

void syscall(){
    
}
