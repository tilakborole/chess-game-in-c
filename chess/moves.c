#include <stdio.h>
#include <stdlib.h>
#include "chesspiece.h"
#include "moves.h"

void init(moves *m) {
	m->i = 0;
}
void push(moves *m, position pos) {
	m->arr[m->i++] = pos;
}

position searchnode(moves *m, int index) {
	return m->arr[index];
}

int ismovesempty(moves *m) {
	return m->i == 0;
}

int ismovesfull(moves *m) {
	return m->i == MAX;
}

int gettotalmoves(moves *m) {
	return m->i;
}

void printmoves(moves *m) {
	int i;
	printf("\n[");
	if(m->i == 0) {
		printf("]\n");
		return;
	}
	for(i = 0; i < m->i; i++) {
		position p = m->arr[i];
		printf("(%d%d%d%d) ", p.currentrow, p.currentcoloumn, p.finalrow, p.finalcoloumn);
	}
	printf("]\n");
}
