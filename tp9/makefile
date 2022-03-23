c=gcc
op=-Wall -Wextra

all : es.o pile.o file.o permut.o tp9.c 	
	$(c) $(op)  es.o file.o pile.o permut.o tp9.c -o tp9
pile.o : pile.c pile.h
	$(c) $(op) -c pile.c	
file.o : file.c file.h
	$(c) $(op) -c file.c
permut.o: permut.c permut.h
	$(c) $(op) -c permut.c
es.o : es.c es.h
	$(c) $(op) -c es.c	

clean:
	rm *.o tp9.exe

