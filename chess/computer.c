#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chesspiece.h"
#include "moves.h"
#include "computer.h"

piece *randomchesspiece(chessboard *cboard) {
	//First find all black pieces
	piece *blackpieces[16];
	int i, j, count = 0;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			if(cboard->board[i][j]->color == 'b') {
				blackpieces[count] = cboard->board[i][j];
				count++;
			}
			
	// generate a random number between 0 & 15 and then selct that index number chess piece form array
	srand((unsigned int)time(NULL));
	int index = rand() % 16;
	piece *random = blackpieces[index];
	return random;
}

moves possiblemoves(piece *chesspiece, chessboard *cboard) {
	moves possible;
	int i, j;
	init(&possible);
	
	position p = getPosition(chesspiece, cboard);
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			p.finalrow = i;
			p.finalcoloumn = j;
			if(cboard->board[i][j]->color != chesspiece->color && checkValidMove(chesspiece, &p, cboard)) {
				if(!(ismovesfull(&possible)))
					push(&possible, p);
			}
		}
	}

	return possible;
}

position getPosition(piece *chesspiece, chessboard *cboard) {
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			if(cboard->board[i][j]->name == chesspiece->name && cboard->board[i][j]->color == chesspiece->color) {
				position p;
				p.currentrow = i;
				p.currentcoloumn = j;
				return p;
			}
	position pp;
	pp.finalrow = -1;
	pp.finalcoloumn = -1;
}

moves checkknockingmove(piece *chesspiece, moves *m, chessboard *cboard) {	//return 1st knocking move
	int i;
	moves knocks;
	init(&knocks);
	int t = gettotalmoves(m);
	for(i = 0; i < t; i++) {
		position pos = m->arr[i];
		if(cboard->board[pos.finalrow][pos.finalcoloumn]->color == 'w' && checkValidMove(chesspiece, &pos, cboard) && !(ismovesfull(&knocks))) {
			push(&knocks, pos);
		}
	}
	return knocks;
}

position chooseComputerMove(chessboard *cboard) {
	int count = 0;	//for 5 times random piece will be selected until no knocking move is found
	moves allpossible, possibleknocks;
	init(&allpossible);
	init(&possibleknocks);
	
	while(1) {
		//First choose chess piece
		piece *selectpiece = randomchesspiece(cboard);
		//Then get move for that piece
		allpossible = possiblemoves(selectpiece, cboard);
		if(!(ismovesempty(&allpossible))) {
			count++;
			possibleknocks = checkknockingmove(selectpiece, &allpossible, cboard);
			if(!(ismovesempty(&possibleknocks))) {
				int totalmoves = gettotalmoves(&possibleknocks);
				int index = rand() % totalmoves;	// 0 to totalmoves - 1
				position pos = searchnode(&possibleknocks, index);
				return pos;
			}
			if(count >= 5 && ismovesempty(&possibleknocks)) {
				int totalpossible = gettotalmoves(&allpossible);
				int i = rand() % totalpossible;
				position pos = searchnode(&allpossible, i);
				return pos;
			}
		}
	}
}

void makeComputerMove(chessboard *cboard) {	//no checking required as moves are already valid
	position pos = chooseComputerMove(cboard);
	if(cboard->board[pos.finalrow][pos.finalcoloumn]->name != 'O')
		printf("COMPUTER KNOCKED OUT YOUR %c !!!\n",cboard->board[pos.finalrow][pos.finalcoloumn]->name);
	
	cboard->board[pos.finalrow][pos.finalcoloumn] = cboard->board[pos.currentrow][pos.currentcoloumn];
	piece *empty = (piece *)malloc(sizeof(piece));
	empty->name = 'O';
	empty->color = ' ';
	cboard->board[pos.currentrow][pos.currentcoloumn] = empty;
}
