cc=gcc -std=c99 -g
exe=chess

$(exe) : king.o pawn.o board.o openSpace.o game.o coordinate.o main.c 
	$(cc) king.o pawn.o board.o openSpace.o game.o coordinate.o main.c -o $(exe)

coordinate.o : coordinate.c coordinate.h
	$(cc) coordinate.c -c

pawn.o : pawn.c pawn.h
	$(cc) pawn.c -c

king.o : king.c king.h
	$(cc) king.c -c

board.o : board.c board.h openSpace.h
	$(cc) board.c -c

openSpace.o : openSpace.c openSpace.h
	$(cc) openSpace.c -c	

game.o : game.c game.h board.h
	$(cc) game.c -c


clean : 
	rm -f *.o
