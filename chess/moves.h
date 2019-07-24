#define MAX 16
typedef struct moves{
	position arr[MAX];
	int i;
}moves;
void init(moves *m);
void push(moves *m, position pos);
position searchnode(moves *m, int index);
int ismovesempty(moves *m);
int ismovesfull(moves *m);
int gettotalmoves(moves *m);
void printmoves(moves *m);

