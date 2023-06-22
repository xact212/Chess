cc=gcc -std=c99
exe=chess

$(exe) : pawn.o board.o openSpace.o game.o main.c 
	$(cc) pawn.o board.o openSpace.o game.o main.c -o $(exe)

pawn.o : pawn.c pawn.h
	$(cc) pawn.c -c

board.o : board.c board.h
	$(cc) board.c -c

openSpace.o : openSpace.c openSpace.h
	$(cc) openSpace.c -c

game.o : game.c game.h
	$(cc) game.c -c

clean : 
	rm -f *.o