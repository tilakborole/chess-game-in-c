
//NOTE THAT COMPUTER PLAYER WILL ALWAYS BE PLAYING IN BLACK PIECES, so no need of passing playercolor as argument in below functions
piece *randomchesspiece(chessboard *cboard);
moves possiblemoves(piece *chesspiece, chessboard *cboard);
moves checkknockingmove(piece *chesspiece, moves *m, chessboard *cboard);	// note current position of all will be same in moves list
position getPosition(piece *chesspiece, chessboard *cboard);	//final coordinates will be 0,0
position chooseComputerMove(chessboard *cboard);
void makeComputerMove(chessboard *cboard);

