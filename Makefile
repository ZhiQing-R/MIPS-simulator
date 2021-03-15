TOPDIR := $(shell pwd)
HDIR := -I $(TOPDIR)/header

assembler: assembler.o freader.o reg_inst.o simulator.o inst_func.o
	gcc -o assembler assembler.o freader.o reg_inst.o inst_func.o simulator.o -g

simulator.o:
	gcc -c $(HDIR) simulator.c -g

assembler.o:
	gcc -c $(HDIR) assembler.c -g

freader.o:
	gcc -c $(HDIR) freader.c -g

reg_inst.o:
	gcc -c $(HDIR) reg_inst.c -g

inst_func.o:
	gcc -c $(HDIR) inst_func.c -g

clean:
	rm -f assembler assembler.o freader.o reg_inst.o inst_func.o simulator.o

