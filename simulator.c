#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freader.h"
#include "reg_inst.h"

int* PC;
long realm;
_Bool llbit = 0;

int main(){
    int* realmPtr = malloc(6*1024*1024);
    realm = (long)realmPtr;
    reg_list[29].val = realm + 6*1024*1024 - 0x400000;
    int* text_end = assemble(realm);
    PC = realm + 0x400000;
    
    return 0; 
}