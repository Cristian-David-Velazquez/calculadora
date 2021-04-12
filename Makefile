CC		:= gcc
AS		:= nasm
ASFLAGS := -f elf32
CFLAGS	:= -m32

all: driver.o

#calc: asm_io.o driver.o first.o
#	$(CC) $(CFLAGS) -o calc first.o driver.c asm_io.o

driver.o: asm_io.o first.o
	$(CC) -o first first.o $(CFLAGS) driver.c asm_io.o

asm_io.o:
	#$(ASM) -f elf -d ELF_TYPE asm_io.asm
	$(AS) $(ASFLAGS) -d ELF_TYPE asm_io.asm

first.o:
	$(AS) $(ASFLAGS) first.asm


#calc: calc.o
#	$(CC) -o calc calc.o 
clean:
	rm *.o *.out calc driver first

#nasm -f elf32 -d ELF_TYPE asm_io.asm
#nasm -f elf32 first.asm
#gcc -o first.o -m32 driver.c asm_io.o

