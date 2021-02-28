TOPDIR := $(shell pwd)
HDIR := -I $(TOPDIR)/header

assembler: assembler.o freader.o reg_inst.o
	gcc -o assembler assembler.o freader.o reg_inst.o -g

assembler.o:
	gcc -c $(HDIR) assembler.c -g

freader.o:
	gcc -c $(HDIR) freader.c -g

reg_inst.o:
	gcc -c $(HDIR) reg_inst.c -g


clean:
	rm -f assembler assembler.o freader.o reg_inst.o

