cc=gcc -std=c99 -g
exe=chess

$(exe) : knight.o queen.o bishop.o rook.o king.o pawn.o board.o openSpace.o game.o coordinate.o main.c 
	$(cc) knight.o queen.o bishop.o rook.o king.o pawn.o board.o openSpace.o game.o coordinate.o main.c -o $(exe)

coordinate.o : coordinate.c coordinate.h
	$(cc) coordinate.c -c

pawn.o : pawn.c pawn.h
	$(cc) pawn.c -c

king.o : king.c king.h
	$(cc) king.c -c

rook.o : rook.c rook.h
	$(cc) rook.c -c

bishop.o : bishop.c bishop.h
	$(cc) bishop.c -c

queen.o : queen.c queen.h
	$(cc) queen.c -c

knight.o : knight.c knight.h
	$(cc) knight.c -c

board.o : board.c board.h openSpace.h
	$(cc) board.c -c

openSpace.o : openSpace.c openSpace.h
	$(cc) openSpace.c -c	

game.o : game.c game.h board.h
	$(cc) game.c -c


clean : 
	rm -f *.o
