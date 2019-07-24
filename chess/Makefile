all: project
project: chess.o play.o computer.o moves.o
	cc chess.o play.o computer.o moves.o -o project
chess.o: chess.c chesspiece.h moves.h computer.h
	cc -c chess.c
play.o: play.c chesspiece.h moves.h computer.h
	cc -c play.c
computer.o: computer.c chesspiece.h moves.h computer.h
	cc -c computer.c
moves.o: moves.c chesspiece.h moves.h
	cc -c moves.c
