cc=gcc -std=c99
exe=chess

$(exe) : pawn.o board.o main.c 
	$(cc) pawn.o board.o main.c -o $(exe)

pawn.o : pawn.c pawn.h
	$(cc) pawn.c -c

board.o : board.c board.h
	$(cc) board.c -c

clean : 
	rm -f *.o