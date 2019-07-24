#define ROWS 8
#define COLOUMNS 8
typedef struct piece{
	char name;	// just single character in capital for name
	char color;	// either 'b' or 'w'
}piece;
typedef struct chessboard{
	piece *board[ROWS][COLOUMNS];
}chessboard;
typedef struct position{
	int currentrow;
	int currentcoloumn;
	int finalrow;
	int finalcoloumn;
}position;
void makeChessBoard(chessboard *cboard);
piece *initPiece(char name, char color);
void drawChessBoard(chessboard *cboard);
int checkValidMove(piece *chesspiece, position *p, chessboard *cboard);
int checkRookMove(char playercolor, position *p, chessboard *cboard);
int checkKnightMove(char playercolor, position *p, chessboard *cboard);
int checkBishopMove(char playercolor, position *p, chessboard *cboard);
int checkKingMove(char playercolor, position *p, chessboard *cboard);	//this function don't see 'check' condition
int checkQueenMove(char playercolor, position *p, chessboard *cboard);
int makeMove(int playernumber, position *p, chessboard *cboard);
int checkCondition(position *p, chessboard *cboard);	//should be called only after move is successful
int checkmate(piece *kingpiece, chessboard *cboard);


