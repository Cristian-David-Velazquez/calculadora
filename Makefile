CC		:= gcc
AS		:= nasm
ASFLAGS := -f elf32
CFLAGS	:= -m32

all: calc

#calc: asm_io.o driver.o first.o
#	$(CC) $(CFLAGS) -o calc first.o driver.c asm_io.o

calc: asm_io.o driver.o first.o suma.o
	$(CC) $(CFLAGS) first.o driver.o asm_io.o suma.o -o calc

asm_io.o: driver.o first.o suma.o
	$(AS) $(ASFLAGS) -d ELF_TYPE asm_io.asm

driver.o: first.o suma.o
	$(CC) $(CFLAGS) -c -o driver.o driver.c

first.o:
	$(AS) $(ASFLAGS) first.asm

suma.o:
	$(AS) $(ASFLAGS) suma.asm


#calc: calc.o
#	$(CC) -o calc calc.o 
clean:
	rm *.o *.out calc driver first

#nasm -f elf32 -d ELF_TYPE asm_io.asm
#nasm -f elf32 first.asm
#gcc -o first.o -m32 driver.c asm_io.o

