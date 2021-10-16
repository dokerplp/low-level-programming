all: main

main: main.o dict.o lib.o
	ld -o main main.o dict.o lib.o

main.o: main.asm colon.inc words.inc
	nasm -felf64 main.asm

lib.o: lib.asm
	nasm -felf64 lib.asm

dict.o: dict.asm
	nasm -felf64 dict.asm
