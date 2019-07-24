#include <stdio.h>
#include <stdlib.h>
#include "chesspiece.h"
#include "moves.h"
#include "computer.h"

void twoplayer();
void singleplayer();

int main() {
	char mode, pass;
	printf("IN THIS GAME 'w' STANDS FOR WHITE PIECES AND 'b' FOR BLACK PIECES\nP: pawn\n:H: Knight\nR : Rook\n B:Bishop\nQ:Queen\nK: King\nEXAMPLE wB means white bishop\n");
	printf("WHITE PIECES ARE FOR PLAYER1\n");
	printf("***ROWS COLOUMNS BOTH ARE NUMBERED FROM 1 TO 8, SO IF YOU WANT TO MAKE A VALID MOVE FIRST GIVE INITIAL COORDINATES AND THEN FINAL COORDINATES EXAMPLE TO MOVE FROM(1, 1) TO (4, 5) GIVE 1 1 4 5 as input.\n");
	printf("***PLEASE ENTER 'S' FOR SINGLE PLAYER MODE AND 'M' FOR MULTIPLAYER MODE***\n");
	scanf("%c", &mode);
	switch(mode) {
		case 'S':
			singleplayer();
			break;
		case 's':
			singleplayer();
			break;
		case 'M':
			twoplayer();
			break;
		case 'm':
			twoplayer();
			break;
		default:
			printf("YOU DIDN'T ENTER CORRECT MODE\n");
	}
	return 0;
}

void twoplayer() {
	chessboard board;
	piece *threat, *wkpiece, *bkpiece;
	position p, m;		//m for check condition and p for input
	char previouscolor, color;
	int playernumber, isMoveSuccess = 0, check = 0;
	makeChessBoard(&board);
	drawChessBoard(&board);
	
	wkpiece = board.board[7][4];
	bkpiece = board.board[0][4];
	
	printf("start the game with white pieces i.e PLAYER1\n");
	playernumber = 1;
	previouscolor = 'b';	//so that white pieces can start the game
	while(scanf("%d %d %d %d", &p.currentrow, &p.currentcoloumn, &p.finalrow, &p.finalcoloumn)) {
		
		p.currentrow = p.currentrow - 1;
		p.currentcoloumn = p.currentcoloumn - 1;
		p.finalrow = p.finalrow - 1;
		p.finalcoloumn = p.finalcoloumn - 1;
		
		if(p.currentrow >= 8 || p.currentrow < 0 || p.currentcoloumn >= 8 || p.currentcoloumn < 0 || p.finalrow >= 8 || p.finalrow < 0 || p.finalcoloumn >= 8 || p.finalcoloumn < 0) {
			printf("INVALID CO ORDINATES PLEASE ENTER AGAIN\n");
			continue;
		}
		
		position bk = getPosition(bkpiece, &board);
		position wk = getPosition(wkpiece, &board);
		//printf("king %d %d\n", bk.currentrow, bk.currentcoloumn);
		
		if(wk.finalrow == -1 || bk.finalrow == -1) {
			printf("KING IS DEAD !!! PLAYER %d HAS LOST!!!", playernumber);
			break;
		}
		if(board.board[p.currentrow][p.currentcoloumn]->color == previouscolor && isMoveSuccess) {
			printf("give other player a chance please\n");
			continue;
		}
		//Then check if previous checkcondition is fulfilled by player
		if(check) {
			int z;
			if(color == 'b') {
				m = getPosition(bkpiece, &board);
				z = checkmate(bkpiece, &board);	//color will not be changed &king's position will be stored in m
			}else{
				m = getPosition(wkpiece, &board);
				z = checkmate(wkpiece, &board);
			}	
			
			
			position pos = getPosition(threat, &board);
			
			m.finalrow = m.currentrow;;
			m.finalcoloumn = m.currentcoloumn;
			m.currentrow = pos.currentrow;
			m.currentcoloumn = pos.currentcoloumn;
			//for reusing instead of declaring new variable
			pos.finalrow = pos.currentrow;
			pos.finalcoloumn = pos.currentcoloumn;
			pos.currentrow = p.currentrow;
			pos.currentcoloumn = p.currentcoloumn;
			if(checkValidMove(board.board[m.currentrow][m.currentcoloumn], &m, &board) || !(checkValidMove(board.board[p.currentrow][p.currentcoloumn], &pos, &board) && p.finalrow == pos.finalrow && p.finalcoloumn == pos.finalcoloumn)){	//problem here!!! if threat is diverted or killed
				printf("MOVE CANNOT HAPPEN DUE TO CHECK CONDITION\n");
				continue;
			}
			else{
				check = 0;
			}
		}
		
		previouscolor = board.board[p.currentrow][p.currentcoloumn]->color;	//updating color
		int isMoveSuccess = makeMove(playernumber, &p, &board);
		if(isMoveSuccess)
			check = checkCondition(&p, &board);
		drawChessBoard(&board);
		
		if(playernumber == 1 && isMoveSuccess)
			playernumber = 2;
		else if(playernumber == 2 && isMoveSuccess)
			playernumber = 1;
		printf("\nPLAYER%d chance :\n", playernumber);
		if(check) {
			printf("\nCHECK!!! KING IS IN DANGER\n");
			//getting color of checked king
			if(board.board[p.finalrow][p.finalcoloumn]->color == 'b')
				color = 'w';
			else if(board.board[p.finalrow][p.finalcoloumn]->color == 'w')
				color = 'b';
			else
				color = ' ';
			threat = board.board[p.finalrow][p.finalcoloumn];
		}
	}
}

void singleplayer() {
	chessboard board;
	piece *threat, *wkpiece, *bkpiece;
	position p, m;		//m for check condition and p for input
	char previouscolor, color;
	int isMoveSuccess = 0, check = 0;
	makeChessBoard(&board);
	drawChessBoard(&board);
	
	wkpiece = board.board[7][4];
	bkpiece = board.board[0][4];
	printf("YOU ARE PLAYING IN WHITE PIECES START !!!\n");

	previouscolor = 'b';	//so that white pieces can start the game
	while(scanf("%d %d %d %d", &p.currentrow, &p.currentcoloumn, &p.finalrow, &p.finalcoloumn)) {
		p.currentrow = p.currentrow - 1;
		p.currentcoloumn = p.currentcoloumn - 1;
		p.finalrow = p.finalrow - 1;
		p.finalcoloumn = p.finalcoloumn - 1;
		
		if(p.currentrow >= 8 || p.currentrow < 0 || p.currentcoloumn >= 8 || p.currentcoloumn < 0 || p.finalrow >= 8 || p.finalrow < 0 || p.finalcoloumn >= 8 || p.finalcoloumn < 0) {
			printf("INVALID CO ORDINATES PLEASE ENTER AGAIN\n");
			continue;
		}
		
		if(board.board[p.currentrow][p.currentcoloumn]->color == previouscolor && isMoveSuccess) {
			printf("give other player a chance please\n");
			continue;
		}

		

		position bk = getPosition(bkpiece, &board);
		position wk = getPosition(wkpiece, &board);
		//printf("king %d %d\n", bk.currentrow, bk.currentcoloumn);
		
		if(wk.finalrow == -1) { // if king is absent!!!
			printf("YOU HAVE LOST KING DEAD!!!\n");
			break;
		}
		if(bk.finalrow == -1) {
			printf("YOU HAVE WON THE GAME !!!\n");
			break;
		}
		
		//Then check if previous checkcondition is fulfilled by player
		if(check) {
			
			int z;
			if(color == 'b') {
				m = getPosition(bkpiece, &board);
				z = checkmate(bkpiece, &board);	//color will not be changed &king's position will be stored in m
			}else{
				m = getPosition(wkpiece, &board);
				z = checkmate(wkpiece, &board);
			}	
			
			position pos = getPosition(threat, &board);
			
			m.finalrow = m.currentrow;;
			m.finalcoloumn = m.currentcoloumn;
			m.currentrow = pos.currentrow;
			m.currentcoloumn = pos.currentcoloumn;
			//for reusing instead of declaring new variable
			pos.finalrow = pos.currentrow;
			pos.finalcoloumn = pos.currentcoloumn;
			pos.currentrow = p.currentrow;
			pos.currentcoloumn = p.currentcoloumn;
			if(checkValidMove(board.board[m.currentrow][m.currentcoloumn], &m, &board) || !(checkValidMove(board.board[p.currentrow][p.currentcoloumn], &pos, &board) && p.finalrow == pos.finalrow && p.finalcoloumn == pos.finalcoloumn)){	//problem here!!! if threat is diverted or killed
				printf("MOVE CANNOT HAPPEN DUE TO CHECK CONDITION\n");
				continue;
			}
			else{
				check = 0;
			}
		}
		
		previouscolor = board.board[p.currentrow][p.currentcoloumn]->color;	//updating color
		int isMoveSuccess = makeMove(1, &p, &board);
		if(isMoveSuccess)
			check = checkCondition(&p, &board);
		drawChessBoard(&board);
		if(!(isMoveSuccess))
			continue;		

		printf("COMPUTER's CHANCE :\n");
		makeComputerMove(&board);	//computer.h move will take place
		drawChessBoard(&board);
		printf("YOUR CHANCE\n");
		
		if(check) {
			printf("\nCHECK!!! KING IS IN DANGER\n");
			//getting color of checked king
			if(board.board[p.finalrow][p.finalcoloumn]->color == 'b')
				color = 'w';
			else if(board.board[p.finalrow][p.finalcoloumn]->color == 'w')
				color = 'b';
			else
				color = ' ';
			threat = board.board[p.finalrow][p.finalcoloumn];
		}
	}
}
