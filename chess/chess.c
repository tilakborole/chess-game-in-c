#include <stdio.h>
#include <stdlib.h>
#include "chesspiece.h"
#include "moves.h"
#include "computer.h"

void makeChessBoard(chessboard *cboard) {
	int i, j;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(i == 1)	//black pawn
				cboard->board[i][j] = initPiece('P', 'b');
			else if(i == 6)	//white pawn
				cboard->board[i][j] = initPiece('P', 'w');
			else if((i == 0 && j == 0) || (i == 0 && j == 7))	//black rook(elephant)
				cboard->board[i][j] = initPiece('R', 'b');
			else if((i == 7 && j == 0) || (i == 7 && j == 7))	//white rook
				cboard->board[i][j] = initPiece('R', 'w');
			else if((i == 0 && j == 1) || (i == 0 && j == 6)) 	//black knight(horse)
				 cboard->board[i][j] = initPiece('H', 'b');
			else if((i == 7 && j == 1) || (i == 7 && j == 6))	//white knight
				cboard->board[i][j] = initPiece('H', 'w');
			else if((i == 0 && j == 2) || (i == 0 && j == 5))	//black bishop(cross)
				cboard->board[i][j] = initPiece('B', 'b');
			else if((i == 7 && j == 2) || (i == 7 && j == 5))	//white bishop
				cboard->board[i][j] = initPiece('B', 'w');
			else if(i == 0 && j == 3)	//black queen
				cboard->board[i][j] = initPiece('Q', 'b');
			else if(i == 7 && j == 3)	//white queen
				cboard->board[i][j] = initPiece('Q', 'w');
			else if(i == 0 && j == 4)	//black king
				cboard->board[i][j] = initPiece('K', 'b');
			else if(i == 7 && j == 4)	//white king
				cboard->board[i][j] = initPiece('K', 'w');
			else 
				cboard->board[i][j] = initPiece('O', ' ');//O indicates there is no piece at that point but we are creating a virtual null piece at that point
			
		}
	}
}
piece *initPiece(char name, char color) {
	piece *p;
	p = (piece *)malloc(sizeof(piece));
	p->name = name;
	p->color = color;
	return p;
}
void drawChessBoard(chessboard *cboard) {
	int i, j;
	printf("  \t");
	for(i = 0; i < 8;i++)
		printf("%d \t", i + 1);
	printf("\n");
	printf("  \t");
	for(i = 0; i < 8; i++)
		printf("---------");
	printf("\n\n");
	for(i = 0; i < 8; i++) {
		printf("%d|\t", i + 1);
		for(j = 0; j < 8; j++) {
			char val = cboard->board[i][j]->name;
			printf("%c%c\t",cboard->board[i][j]->color, val);
		}
		printf("\n\n");
	}
}

int checkValidMove(piece *chesspiece, position *p, chessboard *cboard) {

		//0 if invalid, 1 if valid
	int m, n;
	char name = chesspiece->name;
	char playercolor = chesspiece->color;
	char color = chesspiece->color;
	char c;
	if(color == 'w')
		c = 'b';
	else if(color == 'b')
		c = 'w';
	else
		c = ' ';
	if(p->finalrow >= 8 || p->finalcoloumn >= 8 || p->finalrow < 0 || p->finalcoloumn < 0) // invalid position
		return 0;
	if(p->currentrow == p->finalrow && p->currentcoloumn == p->finalcoloumn)	//same initial and final position
		return 0;
	if(chesspiece->name == 'O')
		return 0;
	switch(color) {
		case 'b':
			switch(name) {
				case 'P':
					m = p->finalrow - p->currentrow;
					n = p->currentcoloumn - p->finalcoloumn;
					if(n < 0)
						n = -n;
					if(m == 1 && (n == 1 || n == 0)) {
						if(n == 0 && cboard->board[p->finalrow][p->finalcoloumn]->color == ' ') {
							return 1;
						}else if(n == 1 && cboard->board[p->finalrow][p->finalcoloumn]->color == c) {
							return 1;
						}else{
							return 0;
						}
					}else if(m == 2 && n == 0) {
						if((p->currentrow == 1 && color == 'b') || (p->currentrow == 6 && color == 'w'))
							return 1;
					}else
						return 0;
				case 'H':
					return checkKnightMove(playercolor, p, cboard);
				case 'B':
					return checkBishopMove(playercolor, p, cboard);
				case 'R':
					return checkRookMove(playercolor, p, cboard);
				case 'Q':
					return checkQueenMove(playercolor, p, cboard);
				case 'K':
					return checkKingMove(playercolor, p, cboard);
				default:
					return 0;
			}
			break;
		case 'w':
			switch(name) {
				case 'P':
					m = p->currentrow - p->finalrow;
					n = p->currentcoloumn - p->finalcoloumn;
					if(n < 0)
						n = -n;
					if(m == 1 && (n == 1 || n == 0)) {
						if(n == 0 && cboard->board[p->finalrow][p->finalcoloumn]->color == ' ') {
							return 1;
						}else if(n == 1 && cboard->board[p->finalrow][p->finalcoloumn]->color == c) {
							return 1;
						}else 
							return 0;
					}else if(m == 2 && n == 0) {
						if((p->currentrow == 1 && color == 'b') || (p->currentrow == 6 && color == 'w'))
							return 1;
					}else
						return 0;
				case 'H':
					return checkKnightMove(playercolor, p, cboard);
				case 'B':
					return checkBishopMove(playercolor, p, cboard);
				case 'R':
					return checkRookMove(playercolor, p, cboard);
				case 'Q':
					return checkQueenMove(playercolor, p, cboard);
				case 'K':
					return checkKingMove(playercolor, p, cboard);
				default :
					return 0;
			}
		default:
			return 0;
	}
}

int checkRookMove(char playercolor, position *p, chessboard *cboard) {  // same for black as well as white piece
	if(cboard->board[p->finalrow][p->finalcoloumn]->color == playercolor)
		return 0;	//checking is required because of logic used in this function
	if(p->currentrow == p->finalrow && p->currentcoloumn != p-> finalcoloumn) {
		int i, j, k, count = 0;
		int n = p->currentcoloumn - p->finalcoloumn; // also need to check that no multiple pieces are present between the positions
		if(n > 0) {
			k = p->currentcoloumn;
			j = p->finalcoloumn;
		}else{
			j = p->currentcoloumn;
			k = p->finalcoloumn;
		}
		for(i = j + 1; i <= k - 1; i++) {
			if(cboard->board[p->currentrow][i]->name != 'O')
				count++;
		}
	
		//now decide on basis of count
		if(count == 0) {
			if(cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor)
				return 1;
			else
				return 0;
			
		}
		if(count == 1) {
			return 0;
		}	
		if(count > 1)
			return 0;
						
	}else if(p->currentcoloumn == p->finalcoloumn && p->currentrow != p->finalrow) {
		
		int i, j, k, count = 0;
		int n = p->currentrow - p->finalrow; // also need to check that no multiple pieces are present between the positions
		if(n > 0) {
			k = p->currentrow;
			j = p->finalrow;
		}else{
			j = p->currentrow;
			k = p->finalrow;
		}
		for(i = j + 1; i <= k - 1; i++) {
			if(cboard->board[i][p->currentcoloumn]->name != 'O')
				count++;
		}
		
		//now decide on basis of count
		if(count == 0) {
			if(cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor)
				return 1;
			else
				return 0;
		}
		if(count == 1) {
			return 0;
		}	
		if(count > 1) 
			return 0;					
			
	}else
		return 0;
}

int checkKnightMove(char playercolor, position *p, chessboard *cboard) {
	
	int m = p->currentrow - p->finalrow;
	int n = p->currentcoloumn - p->finalcoloumn;
	if(n < 0)
		n = -n;
	if(m < 0)
		m = -m;
	if(m == 2 && n == 1 && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))
		return 1;
	else if(m == 1 && n == 2 && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))
		return 1;
	else 
		return 0;
}

int checkBishopMove(char playercolor, position *p, chessboard *cboard) {
	/* we need to check the difference between rows and columns of initial and final position, then based on them visualize 4 different paths*/
	int flag, i, j, count;
	if(p->finalrow > p->currentrow && p->finalcoloumn > p->currentcoloumn)
		flag = 1;	//lower right diagonal checking
	else if(p->finalrow > p->currentrow && p->finalcoloumn < p->currentcoloumn)
		flag = 2;    	//lower left diagonal checking
	else if(p->finalrow < p->currentrow && p->finalcoloumn < p->currentcoloumn)
		flag = 3;	//upper left diagonal checking
	else if(p->finalrow < p->currentrow && p->finalcoloumn > p->currentcoloumn)
		flag = 4;	// upper right diagonal checking
	else
		return 0;		//if final position is in horizontal or vertical direction
		
	int rowdifference = p->finalrow - p->currentrow;
	int coloumndifference = p->finalcoloumn - p->currentcoloumn;
	if(rowdifference < 0)
		rowdifference = -rowdifference;
	if(coloumndifference < 0)
		coloumndifference = -coloumndifference;
	
	if(rowdifference != coloumndifference)	// dosn't belong to any diagonal
		return 0;
	
	/*switch statement is used to see if we have multiple pieces or player piece in the path between current and final positions.*/
	switch(flag) {
		case 1:	//lower right diagonal
			i = p->currentrow;
			j = p->currentcoloumn;
			count = 0;
			i++;
			j++;
			while(i <= p->finalrow && j <= p->finalcoloumn) {
				if(cboard->board[i][j]->name != 'O' && cboard->board[i][j]->color != playercolor)
					count++;
				if(cboard->board[i][j]->color == playercolor) {
					count = -1;	//invalid due to player piece between path
					break;
				}	
				i++;
				j++;
			}
			if(count == 0)	// no piece i path
				return 1;
			else if(count == 1 && (cboard->board[p->finalrow][p->finalcoloumn]->name != 'O') && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))	//knock opponent piece
				return 1;
			else
				return 0;
			
		case 2:	//lower left diagonal
			i = p->currentrow;
			j = p->currentcoloumn;
			count = 0;
			i++;
			j--;
			while(i <= p->finalrow && j >= p->finalcoloumn) {
				if(cboard->board[i][j]->name != 'O' && cboard->board[i][j]->color != playercolor)
					count++;
				if(cboard->board[i][j]->color == playercolor) {
					count = -1;	//invalid due to player piece between path
					break;
				}	
				i++;
				j--;
			}
			if(count == 0)	// no piece i path
				return 1;
			else if(count == 1 && (cboard->board[p->finalrow][p->finalcoloumn]->name != 'O') && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))	//knock opponent piece
				return 1;
			else
				return 0;
		
		case 3:	//upper left diagonal
			i = p->currentrow;
			j = p->currentcoloumn;
			count = 0;
			i--;
			j--;
			while(i >= p->finalrow && j >= p->finalcoloumn) {
				if(cboard->board[i][j]->name != 'O' && cboard->board[i][j]->color != playercolor)
					count++;
				if(cboard->board[i][j]->color == playercolor) {
					count = -1;	//invalid due to player piece between path
					break;
				}	
				i--;
				j--;
			}
			if(count == 0)	// no piece i path
				return 1;
			else if(count == 1 && (cboard->board[p->finalrow][p->finalcoloumn]->name != 'O') && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))	//knock opponent piece
				return 1;
			else
				return 0;
		
		case 4:	//upper right diagonal
			i = p->currentrow;
			j = p->currentcoloumn;
			count = 0;
			i--;
			j++;
			while(i >= p->finalrow && j <= p->finalcoloumn) {
				if(cboard->board[i][j]->name != 'O' && cboard->board[i][j]->color != playercolor)
					count++;
				if(cboard->board[i][j]->color == playercolor) {
					count = -1;	//invalid due to player piece between path
					break;
				}	
				i--;
				j++;
			}
			if(count == 0)	// no piece i path
				return 1;
			else if(count == 1 && (cboard->board[p->finalrow][p->finalcoloumn]->name != 'O') && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))	//knock opponent piece
				return 1;
			else
				return 0;
		default:
			return 0;
		
	}
	
}

int checkKingMove(char playercolor, position *p, chessboard *cboard) {
	/*if scope goes beyond the chessboard ie less than 0 or more than 7, then dont worry because that is alredy handled from function it is called*/
	int rowdifference = p->finalrow - p->currentrow;
	int coloumndifference = p->finalcoloumn - p->currentcoloumn;
	if(rowdifference < 0)
		rowdifference = -rowdifference;
	if(coloumndifference < 0)
		coloumndifference = -coloumndifference;
		
	if(rowdifference == 1 && coloumndifference == 1 &&(cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))	//diagonal
		return 1;	//diagonal (applied in prevoius function as well)
	else if(rowdifference == 0 && coloumndifference == 1 && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))
		return 1;	//left and right position
	else if(rowdifference == 1 && coloumndifference == 0 && (cboard->board[p->finalrow][p->finalcoloumn]->color != playercolor))
		return 1;	//top and bottom position
	else 
		return 0;
		
}

int checkQueenMove(char playercolor, position *p, chessboard *cboard){
	int i = checkRookMove(playercolor, p, cboard);
	int j = checkBishopMove(playercolor, p, cboard);
	if(i || j)	//as queen is combination of bishop and rook
		return 1;
	else
		return 0;
}

int makeMove(int playernumber, position *p, chessboard *cboard) {
	piece *selected = cboard->board[p->currentrow][p->currentcoloumn];
	int validMove = checkValidMove(selected, p, cboard);
	if(validMove && (cboard->board[p->finalrow][p->finalcoloumn]->name != 'O')) {
		printf("player %d knocked out other player's %c !!!\n", playernumber, cboard->board[p->finalrow][p->finalcoloumn]->name);
	}
	if(validMove) {
		piece *emptypiece = (piece *)malloc(sizeof(piece));
		emptypiece->name = 'O';	//creating an empty virtual piece 
		emptypiece->color = ' ';
		
		//Now make move
		cboard->board[p->finalrow][p->finalcoloumn] = cboard->board[p->currentrow][p->currentcoloumn];
		cboard->board[p->currentrow][p->currentcoloumn] = emptypiece;
		return 1;
		
	}else{
		printf("\nMove is not valid\n");
		return 0;
	}
}

int checkCondition(position *p, chessboard *cboard){	//note function is called after making move, so position of piece is in final
	piece *movedpiece;
	movedpiece = cboard->board[p->finalrow][p->finalcoloumn];
	int isCheck;
	char movedpiececolor = cboard->board[p->finalrow][p->finalcoloumn]->color;
	
	position *simulate = (position *)malloc(sizeof(position));
	simulate->currentrow = p->finalrow;
	simulate->currentcoloumn = p->finalcoloumn;
	
	/*in this function we have to just simulate move between piece and the other player's king and if that move is prediceted a s successful then, it's a check condition*/
	//First search for opponent king
	char color;
	if(movedpiececolor == 'b')
		color = 'w';
	else
		color = 'b';
	piece *kpiece = (piece *)malloc(sizeof(piece));
	kpiece->name = 'K';
	kpiece->color = color;
	position m = getPosition(kpiece, cboard);
	simulate->finalrow = m.currentrow;
	simulate->finalcoloumn = m.currentcoloumn;
	
	isCheck = checkValidMove(movedpiece, simulate, cboard);
	return isCheck;
	
}

int checkmate(piece *kingpiece, chessboard *cboard){
	moves m;
	m = possiblemoves(kingpiece, cboard);
	if(ismovesempty)
		return 1;
	else 
		return 0;
}
