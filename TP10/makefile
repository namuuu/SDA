c=gcc
op= -Wall -Wextra

all: tp10.exe

tp10.exe: prod.h util.o main.c
	$(c) $(op) prod.h util.o main.c -o tp10.exe

util.o: util.c util.h
	$(c) $(op) -c util.c

clean:
	rm -rf *.o
	rm -rf *.exe