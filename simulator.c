#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freader.h"
#include "reg_inst.h"

int main(){
    int* realm = malloc(6*1024*1024);
    reg_list[29].val = (int)realm + 6*1024*1024 - 0x400000;
    int* text_end = assemble(realm);
    int* PC = realm;
    
    return 0; 
}