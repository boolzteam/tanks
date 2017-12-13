#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <stdlib.h>

#define N 30
typedef enum {FALSE,TRUE}bool;

typedef struct Tank1
{
	char name;
	bool live;
	int life;
	int x;
	int y;

}*Tank1;
typedef struct Tank2
{
	char name;
	bool live;
	int life;
	int x;
	int y;

}*Tank2;
typedef struct Tank3
{
	char name;
	bool live;
	int life;
	int x;
	int y;

}*Tank3;
typedef struct Tank4
{
	char name;
	bool live;
	int life;
	int x;
	int y;

}*Tank4;

typedef struct GameBoard
{
	char mat[N][N];
	

}*GameBoard;



GameBoard *initialize(int players);

int main()
{
	int players;
	printf("Enter the number of players:");
	scanf("%d", &players);
	struct GameBoard * temp = NULL;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			temp->mat[i][j] = 'X';
	initialize(players);
	struct Tank3 *blabla=NULL;
	printf("%c", blabla->name);
	return 0;
}


GameBoard *initialize(int players)
{
	struct GameBoard * temp = NULL;
	//for (int i = 0; i < N; i++)
		//for (int j = 0; j < N; j++)
			//temp->mat[i][j] = 'X';    //initialize board
	if (players >= 1)
	{
		struct Tank1 * p = NULL;
		p->name = 'A';
		p->live = TRUE;
		p->life = 2;
		p->x = 3;
		p->y = 2;
		temp->mat[p->x][p->y] = p->name;
	}
	if (players >= 2)
	{
		struct Tank2 * p = NULL;
		p->name = 'B';
		p->live = TRUE;
		p->life = 2;
		p->x = 12;
		p->y = 5;
		temp->mat[p->x][p->y] = p->name;
	}
	if (players >= 3)
	{
		struct Tank3 * p = NULL;
		p->name = 'C';
		p->live = TRUE;
		p->x = 13;
		p->y = 5;
		temp->mat[p->x][p->y] = p->name;
	}
	if (players == 4)
	{
		struct Tank4 * p = NULL;
		p->name = 'D';
		p->live = TRUE;
		p->x = 21;
		p->y = 5;
		temp->mat[p->x][p->y] = p->name;
	}
	return temp;
}

