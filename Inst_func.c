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

void xor(reg* rd, reg* rs, reg* rt){
    rd->val = rs->val ^ rt->val;
}

void xori(reg* rt, reg* rs, int imm){
    rt->val = rs->val ^ imm;
}

