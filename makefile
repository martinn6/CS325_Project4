default: project04

project04: Project04.c
	gcc -std=c99 -o project04 Project04.c

all: project04

clean:
	rm -f *.o project04.exe
