#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
//#include "Minunit.h"
#define N 50
#define M 224
#define M_PI 3.14159265358979323846 
typedef enum { FALSE, TRUE }bool;

typedef struct
{
	char name;
	bool live;
	int life;
	int x;
	int y;
	char nameP[M];
	char ID[M];

}Tank;
int globalcount = 0;
/*
bool Test_ID(char* id);
bool Test_Move_Direction(int num);
bool Test_Move_Size(int num);
bool Test_Choose_Shot(int num);
bool Test_Angle_Shot(double num);
bool Test_Power_Shot(double num);
bool Test_Positive_Log(double num);*/
Tank ** initialize(int players, char Board[N][M]);
void Play(char Board[N][M], Tank** Arr, int players);
void PrintBoard(char Board[N][M]);
void Move(Tank* tank, char Board[N][M]);
void Shoot(Tank* tank, char Board[N][M], Tank** Arr);
void Directshot(Tank* tank, char map[N][M], Tank ** arr);
void BuildMap(char map[N][M]);
void Guided_Missile(Tank* tank, char map[N][M]);
double Log_By_Base(double value, double wanted_base);
bool Test_ID(char* id);
void Steep_path(Tank* tank, char map[N][M], Tank **arr);
void CrazySheep(Tank* tank, char map[N][M], Tank ** arr);
int hit(Tank* tank, char map[N][M], Tank ** arr, int tempX, int tempY, int i, int power, char tempMap[N][M]);
bool glob_hit(Tank* tank, char map[N][M], Tank ** arr, int x, int y);
double make_a_positive(double);
int main()
{

	//bool *test[7];
	char GameBoard[50][224];
	BuildMap(GameBoard);
	PrintBoard(GameBoard);

	int players = 5;
	Tank ** Arr = NULL;
	while (players > 4 || players < 2)
	{
		printf("Enter number of players\n");
		scanf("%d", &players);
	}
	Arr = initialize(players, GameBoard);
	PrintBoard(GameBoard);
	Play(GameBoard, Arr, players);
	for (int i = 0; i < players; i++) // free memory
		free(Arr[i]);
	free(Arr);
	for (int i = 0; i < 10; i++)
		printf("\ndid you change the STEPS?!??!?\nfrom 50 to 5\nfunction move....\n");

	return 0;
}
void BuildMap(char map[N][M])
{
	strcpy(map[0], "                                                                                                                                                                                                                               ");
	strcpy(map[1], "                                                                                                                                                                                                                               ");
	strcpy(map[2], "                                                                                                                                                                                                                               ");
	strcpy(map[3], "                                                                                                                                                                                                                               ");
	strcpy(map[4], "                                                                                                                                                                                                                               ");
	strcpy(map[5], "                                                                                                                                                                                                                               ");
	strcpy(map[6], "                                                                                                                                                                                                                               ");
	strcpy(map[7], "                                                                                                                                                                                                                               ");
	strcpy(map[8], "                                                                                                                                                                                                                               ");
	strcpy(map[9], "                                                                                                                                                                                                                               ");
	strcpy(map[10], "                                                                                                                                                                                                                               ");
	strcpy(map[11], "                                                                                                                                                                                                                               ");
	strcpy(map[12], "                                                                                                                                                                                                                               ");
	strcpy(map[13], "                                                                                                                                                                                                                               ");
	strcpy(map[14], "                                                                                                                                                                                                                               ");
	strcpy(map[15], "                                                                                                                                                                                                                               ");
	strcpy(map[16], "                                                                                                                                                                                                                               ");
	strcpy(map[17], "                                                                                                                                                                                                                               ");
	strcpy(map[18], "                                                                                                                                                                                                                               ");
	strcpy(map[19], "                                       |                                                                                                                                                                                       ");
	strcpy(map[20], "                                      |||                                                                                                                                                                                      ");
	strcpy(map[21], "                                     |||||                                                                                                                                                                                     ");
	strcpy(map[22], "                                    |||||||                                                                                                                                                                                    ");
	strcpy(map[23], "                                   |||||||||                                                                                                                                                                                   ");
	strcpy(map[24], "                                  |||||||||||                                                                                                                                                                                  ");
	strcpy(map[25], "                                 |||||||||||||                                                                                                                                                                                 ");
	strcpy(map[26], "                                |||||||||||||||                                                                                                                                                                                ");
	strcpy(map[27], "                               |||||||||||||||||                                                                                                                                                                               ");
	strcpy(map[28], "                              |||||||||||||||||||                                                                                                                                                                              ");
	strcpy(map[29], "                             |||||||||||||||||||||                                                                                                                                                                             ");
	strcpy(map[30], "                            |||||||||||||||||||||||                                                                                                                                                                            ");
	strcpy(map[31], "                           |||||||||||||||||||||||||                                                                                                                                                                           ");
	strcpy(map[32], "                          |||||||||||||||||||||||||||              |                                                                                                                                                           ");
	strcpy(map[33], "                         |||||||||||||||||||||||||||||            |||                                                                                                                                                          ");
	strcpy(map[34], "                        |||||||||||||||||||||||||||||||          |||||                                                                                                                                                         ");
	strcpy(map[35], "                       |||||||||||||||||||||||||||||||||        |||||||               |                                                                                                                                        ");
	strcpy(map[36], "                      |||||||||||||||||||||||||||||||||||      |||||||||             |||                                                                                                                                       ");
	strcpy(map[37], "                     |||||||||||||||||||||||||||||||||||||    |||||||||||           |||||                                                                                                                                      ");
	strcpy(map[38], "                    |||||||||||||||||||||||||||||||||||||||  |||||||||||||         |||||||                                                                                                                                     ");
	strcpy(map[39], "            |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||       |||||||||                                                                                                                                    ");
	strcpy(map[40], "          ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||     |||||||||||                                                                                                                                   ");
	strcpy(map[41], "        |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||   |||||||||||||                                           |                                                            |                         ");
	strcpy(map[42], "       ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| |||||||||||||||                                         |||                                                          |||                        ");
	strcpy(map[43], "      |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||                                       |||||                                                        |||||                       ");
	strcpy(map[44], "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||                                     |||||||                                                      |||||||                      ");
	strcpy(map[45], "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||                                   |||||||||                        |                           |||||||||                     ");
	strcpy(map[46], "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||                                 |||||||||||                      |||                         |||||||||||                    ");
	strcpy(map[47], "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||             |                 |||||||||||||                    |||||                       |||||||||||||                   ");
	strcpy(map[48], "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||           |||               |||||||||||||||                  |||||||                     |||||||||||||||                  ");
	strcpy(map[49], "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}
void PrintBoard(char Board[N][M])
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 224; j++)
			printf("%c", Board[i][j]);
	}
}
Tank ** initialize(int players, char Board[N][M])
{
	int j = 0;//counter to id
	int counter_ID = 0;
	bool flag_ID = FALSE;
	bool flag = FALSE;
	char c = 'A';
	srand(time(NULL));
	Tank ** Arr = (Tank**)malloc((sizeof(Tank))*players);
	for (int i = 0; i < players; i++, c++)
	{
		Arr[i] = (Tank*)malloc(sizeof(Tank));
		Arr[i]->live = TRUE;
		Arr[i]->life = 2;
		Arr[i]->name = c;
		printf("Enter the name of player %d\n", i + 1);
		scanf("%s", &Arr[i]->nameP);
		printf("Enter the ID of player %d (9 digits)\n", i + 1);
		do {
			scanf("%s", &Arr[i]->ID);
		} while (Test_ID(Arr[i]->ID) == FALSE);
		if (i == players - 1)
		{
			switch (players)
			{
			case 1:
				printf("You have some serious troubles.\n");
				break;
			case 2:
				Arr[0]->y = rand() % 111;
				Arr[0]->x = 49;
				Arr[1]->y = 111 + (rand() % 111);
				Arr[1]->x = 49;
				break;
			case 3:
				Arr[0]->y = rand() % 73;
				Arr[0]->x = 49;
				Arr[1]->y = 73 + (rand() % 73);
				Arr[1]->x = 49;
				Arr[2]->y = 146 + (rand() % 73);
				Arr[2]->x = 49;
				break;
			case 4:
				Arr[0]->y = rand() % 55;
				Arr[0]->x = 49;
				Arr[1]->y = 55 + (rand() % 55);
				Arr[1]->x = 49;
				Arr[2]->y = 110 + (rand() % 55);
				Arr[2]->x = 49;
				Arr[3]->y = 165 + (rand() % 55);
				Arr[3]->x = 49;
				break;
			}
			for (int j = 0; j < players; j++)
			{
				if (Board[Arr[j]->x][Arr[j]->y] != ' ')
					while (Board[Arr[j]->x - 1][Arr[j]->y] != ' ')
						Arr[j]->x = Arr[j]->x - 1;
				Arr[j]->x = Arr[j]->x - 1;
				Board[Arr[j]->x][Arr[j]->y] = Arr[j]->name;
			}
		}
	}
	return Arr;
}
void Play(char Board[N][M], Tank** Arr, int players)
{
	globalcount = players;
	int choose;
	while (globalcount > 1)
	{
		for (int i = 0; i < players; i++)
			if (Arr[i]->live == TRUE)
			{
				printf("Its %s turn!\n", Arr[i]->nameP);
				printf("would you like to move?1-Yes,0-No\t");
				scanf("%d", &choose);
				if (choose)
					Move(Arr[i], Board);
				Shoot(Arr[i], Board, Arr);
			}
	}
	for (int i = 0; i < players; i++)
		if (Arr[i]->live == TRUE)
			printf("\n%s won the game!\n", Arr[i]->nameP);
}
void Move(Tank* tank, char Board[N][M])
{
	PrintBoard(Board);
	int choose, step;
	Board[tank->x][tank->y] = ' ';
	printf("What direction you want to move? Left-1, Right-2 \t");
	scanf("%d", &choose);
	printf("Enter how many steps do you want to move\t");
	scanf("%d", &step);
	while (step > 50 || step < 0)
	{
		printf("Maximum 5 moves,Enter how many steps do you want to move\t");
		scanf("%d", &step);
	}
	if (choose == 1)//chose left
		step = step*(-1);
	if (tank->y + step >= M)//áãé÷ú âáåìåú îòøê
		tank->y = M - 1;
	else if (tank->y + step < 0)
		tank->y = 0;
	else
		tank->y = tank->y + step;//äåñôú öòãéí ìèð÷
	if (Board[tank->x][tank->y] == ' ')
	{
		while (Board[tank->x + 1][tank->y] == ' ')
			tank->x = tank->x + 1;
		if (Board[tank->x][tank->y] == '|')
			tank->x = tank->x - 1;
	}
	else if (Board[tank->x][tank->y] != ' ')
	{
		while (Board[tank->x - 1][tank->y] != ' ')
			tank->x = tank->x - 1;
		if (Board[tank->x][tank->y] == '|')
			tank->x = tank->x - 1;
	}
	if (tank->x == 49)
		tank->x = tank->x - 1;
	Board[tank->x][tank->y] = tank->name;
	PrintBoard(Board);
}
void Shoot(Tank* tank, char Board[N][M], Tank** Arr)
{
	int choose;
	printf("Enter what kind of shoot do you want:\n1.Direct shot.\n2.Steep path\n3.Guided Missile.\n4.Crazy sheep.\n");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
		Directshot(tank, Board, Arr);
		break;
	case 2:
		Steep_path(tank, Board, Arr);
		break;
	case 3:
		Guided_Missile(tank, Board);
		break;
	case 4:
		CrazySheep(tank, Board, Arr);
		break;
	}
}
void Directshot(Tank* tank, char map[N][M], Tank ** arr)
{
	int power = 0, tempX = 0, index = 0, x;
	double angel = 0, tempY = 0;
	char tempMap[N][M];
	for (int i = 0; i<N; i++)
		for (int j = 0; j<M; j++)
			tempMap[i][j] = map[i][j];

	printf("Enter Angel and Power:\n");
	double radian;
	scanf("%lf%d", &angel, &power);
	if (angel < 90)
		radian = angel / 180 * M_PI; // convert to 
	else
	{
		printf("\nrad:%d\n", (int)angel % 90);
		radian = (((int)angel % 90)* M_PI / 180);
	}
	printf("\n %lf \n", radian);
	//double radian = tan(angel);
	tempX = tank->x;
	tempY = tank->y;
	radian++;
	for (int i = 1; i <= power; i++)
	{
		if (angel < 90)
		{
			tempX = tempX - radian;
			x = tempX;
			tempY = tempY + 2;
		}
		else if (angel > 90 && angel < 180)
		{
			tempX = tempX - radian;
			x = tempX;
			tempY = tempY - 2;
		}
		else if (angel > 180 && angel < 270)
		{
			tempX = tempX + radian;
			x = (int)tempX;
			tempY = tempY - 2;
		}
		else if (angel > 270 && angel < 360)
		{
			tempX = tempX + radian;
			x = tempX;
			tempY = tempY + 2;
		}
		else if (angel == 0 || angel == 360)
			tempY = tempY + 2;
		else if (angel == 90)
		{
			tempX = tempX - radian;
			x = tempX;

		}
		else if (angel == 180)
			tempY = tempY - 2;
		else if (angel == 270)
		{
			tempX = tempX + radian;
			x = tempX;
		}
		i = hit(tank, map, arr, x, (int)tempY, i, power, tempMap);
	}
	PrintBoard(tempMap);
}
int hit(Tank* tank, char map[N][M], Tank ** arr, int tempX, int tempY, int i, int power, char tempMap[N][M]) {
	if (map[tempX][(tempY)] == 'A' || map[tempX][(tempY)] == 'B' || map[tempX][(tempY)] == 'C' || map[tempX][(tempY)] == 'D')
	{
		switch (map[tempX][(tempY)])
		{
		case 'A':
			arr[0]->life--;
			printf("HIT ! ! !\n");
			if (arr[0]->life == 0)
			{
				arr[0]->live = FALSE;
				globalcount--;
				printf("Player %s is dead.\n", arr[0]->nameP);
				map[arr[0]->x][arr[0]->y] = ' ';
			}
			break;
		case 'B':
			arr[1]->life--;
			printf("HIT ! ! !\n");
			if (arr[1]->life == 0)
			{
				arr[1]->live = FALSE;
				globalcount--;
				printf("Player %s is dead.\n", arr[1]->nameP);
				map[arr[1]->x][arr[1]->y] = ' ';
			}
			break;
		case 'C':
			arr[2]->life--;
			printf("HIT ! ! !\n");
			if (arr[2]->life == 0)
			{
				arr[2]->live = FALSE;
				globalcount--;
				printf("Player %s is dead.\n", arr[2]->nameP);
				map[arr[2]->x][arr[2]->y] = ' ';
			}
			break;
		case 'D':
			arr[3]->life--;
			printf("HIT ! ! !\n");
			if (arr[3]->life == 0)
			{
				arr[3]->live = FALSE;
				globalcount--;
				printf("Player %s is dead.\n", arr[3]->nameP);
				map[arr[3]->x][arr[3]->y] = ' ';
			}
			break;
		}
	}
	if (tempMap[tempX][(int)round(tempY)] == '|')
		return power;
	else if (tempX > N - 1 || tempX < 0 || tempY < 0 || tempY >M - 1)
		return power;
	else if (tempMap[tempX][(int)round(tempY)] == 'A' || tempMap[tempX][(int)round(tempY)] == 'B' || tempMap[tempX][(int)round(tempY)] == 'C' || tempMap[tempX][(int)round(tempY)] == 'D')
	{
		tempMap[tempX][(int)round(tempY)] = 'X';
		return power;
	}
	else
	{
		tempMap[tempX][(int)round(tempY)] = '*'; //print 1 shot 
		return i;
	}

}

bool glob_hit(Tank* tank, char map[N][M], Tank ** arr, int x, int y) {
	int i;
	if ((map[x][y] == 'A' || map[x][y] == 'B' || map[x][y] == 'C' || map[x][y] == 'D') && tank->x != x && tank->y != y)
	{
		switch (map[x][y])
		{
		case 'A':
			i = 0;
			break;
		case 'B':
			i = 1;
			break;
		case 'C':
			i = 2;
			break;
		case 'D':
			i = 3;
			break;
		default:
			break;
		}
		arr[i]->life--;
		printf("HIT ! ! !\n");
		if (arr[i]->life == 0)
		{
			arr[i]->live = FALSE;
			globalcount--;
			printf("Player %s is dead.\n", arr[0]->nameP);
			map[arr[i]->x][arr[i]->y] = ' ';
		}
		return TRUE;
	}
	return FALSE;
}

double Log_By_Base(double value, double wanted_base)
{
	double newVal = 0;
	newVal = log(value) / log(wanted_base);
	return newVal;
}
void Guided_Missile(Tank* tank, char map[N][M])
{
	int power = 0, dir = 0, index = 0, tempX = 0, x, y;
	double angel = 0, base = 0, tempY = 0;
	char tempMap[N][M];
	for (int i = 0; i<N; i++)
		for (int j = 0; j<M; j++)
			tempMap[i][j] = map[i][j];

	printf("Enter base and Power:\n");
	scanf("%lf%d", &base, &power);
	//printf("Which Direction?\t left 0, right 1\t");
	//scanf("%d", &dir);
	//if(dir==0)
	x = tank->x;
	y = tank->y;
	tempX = tank->x;
	tempY = tank->y;
	int i = 0, j = 0;
	//tempMap[tempX-1][y] = '-';
	//tempMap[tempX - 2][y] = '-';

	while (i <= power)
	{

		printf("\n(x=%d,y=%lf)\n", tempX, tempY);
		if (map[(int)tempX - 1][(int)tempY] == '|' || map[(int)tempX][(int)tempY + 1] == '|')
			break;
		if (tempY == 0)
			tempY = Log_By_Base(tank->y, base);
		tempY = i*(Log_By_Base(tempY, base));
		tempY = round(tempY);
		if (i == 0)
			tempX -= 1;
		if (i != 0)
			if (i <= power / i)
				tempX -= 1;

		if (map[tempX][(int)tempY] == 'A' || map[tempX][(int)tempY] == 'B' || map[tempX][(int)tempY] == 'C' || map[tempX][(int)tempY] == 'D')
		{
			switch (map[tempX][(int)tempY])
			{
			case 'A':
				tank->life--;
				if (tank->life == 0)
				{
					tank->live = FALSE;
					map[tank->x][tank->y] = ' ';
				}
				break;
			case 'B':
				tank->life--;
				if (tank->life == 0)
				{
					tank->live = FALSE;
					map[tank->x][tank->y] = ' ';
				}
				break;
			case 'C':
				tank->life--;
				if (tank->life == 0)
				{
					tank->live = FALSE;
					map[tank->x][tank->y] = ' ';
				}
				break;
			case 'D':
				tank->life--;
				if (tank->life == 0)
				{
					tank->live = FALSE;
					map[tank->x][tank->y] = ' ';
				}
				break;
			}
		}
		if (i == 0)
			tempMap[tempX - i][(int)tempY + y] = '*';
		else
			tempMap[tempX - i][(int)tempY + y - 2] = '*'; //print 1 shot     int)tempY+y
														  //PrintBoard(tempMap);											  //tempY = round(tempY); // final Y index.

		printf("\n(x=%d,y=%lf)\n", tempX - i, tempY);
		printf("\ntank y %d\n", tank->y);
		i++;
	}
	//tempMap[tempX - i][(int)tempY + y + i] = '*';
	//	printf("tempX:%d\n", tempX);
	//	tempMap[tempX][(int)round(tempY)] = '*'; //print 1 shot
	PrintBoard(tempMap);
}
bool Test_ID(char* id)//return true if id has 9 nums 
{
	if (strlen(id) != 9)
	{
		printf("Wrong input! ID number consist 9 digits only, Please try again\n");
		return FALSE;
	}
	for (int i = 0; id[i] != '\0'; i++)
		if (id[i] > '9' || id[i] < '0')
		{
			printf("Wrong input! ID number consist 9 digits only, Please try again\n");
			return FALSE;
		}
	return TRUE;
}

void Steep_path(Tank* tank, char map[N][M], Tank **arr) 
{
	char tempmap[N][M];
	for (int i = 0; i<N; i++)
		for (int j = 0; j<M; j++)
			tempmap[i][j] = map[i][j];
	char d = 'a';
	bool done = FALSE;
	double a, b, c, y, prev_y = 0;
	int tankx=tank->x,tanky=tank->y, dx, x, real_y, temp_y, direction;
	do
	{
		printf("Which direction do you want to shoot? 1-Left  2-Right\n");
		getchar();
		scanf("%c", &d);
		getchar();
		if (d == '1')
			direction = 1;
		else if (d == '2')
			direction = 2;
		else
		{
			printf("Worng input, Please try again!\nPlease read the instructions!\n");
		}
	} while (d != '1' && d != '2');
	printf("Enter coefficients of Quadratic Equation aX^2 + bX +c (a,b,c): \n");
	scanf("%lf%lf%lf", &a, &b, &c);
	if (a >= 0)
		a = make_a_positive(a);
	for (int i = 0; i < 2 * M && done == FALSE; i++) //axel wide
	{
		dx = N - 1 - tankx;
		y = a*i*i + b*i;
		for (int j = N - 1 - dx - (int)round(prev_y); j > N - 1 - dx - (int)round(y) && done == FALSE; j--)//print up
		{
			if (direction == 2)
				temp_y = i - 1 + tanky;
			else
				temp_y = tanky - i;
			if (tempmap[j][temp_y] == '|' || j < 0 || j >= N || temp_y < 0 || temp_y >= M)
			{
				done = TRUE;
				break;
			}
			if (glob_hit(tank, map, arr, j, temp_y) == TRUE)
			{
				done = TRUE;
				break;
			}
			if (tempmap[j][temp_y] == ' ')
				tempmap[j][temp_y] = '*';
		}
		for (int j = N - dx - (int)round(prev_y); j < N - dx - (int)round(y) && done == FALSE; j++)//print down
		{
			if (direction == 2)
				temp_y = i - 1 + tanky;
			else
				temp_y = tanky - i;
			if (tempmap[j][temp_y] == '|' || j < 0 || j >= N || temp_y < 0 || temp_y >= M)
			{
				done = TRUE;
				break;
			}
			if (glob_hit(tank, map, arr, j, temp_y) == TRUE)
			{
				done = TRUE;
				break;
			}
			if(tempmap[j][temp_y]==' ')
				tempmap[j][temp_y] = '*';
		}

		x = N - 1 - dx - (int)round(y);
		if (direction == 2)
			real_y = i + tanky;
		else
			real_y = tanky - i - 1;

		if (done == TRUE || tempmap[x][real_y] == '|' || x < 0 || x >= N || real_y < 0 || real_y >= M)
			break;
		if (glob_hit(tank, map, arr, x, real_y) == TRUE)
		{
			done = TRUE;
			break;
		}
		if (y > prev_y && tempmap[x][real_y]==' ')
			tempmap[x][real_y] = '*';
		prev_y = y;
	}
	PrintBoard(tempmap);
}

double make_a_positive(double a) {
	do {
		printf("'a' must be a negative number, please change your choise\n");
		scanf("%lf", &a);
	} while (a >= 0);
	return a;
}

void CrazySheep(Tank* tank, char map[N][M], Tank ** arr)
{
	int power = 0, index = 0, a, b, My_NewPI = 21, y = 0, max, direct;
	double angel = 0, x = 0;
	char tempMap[N][M];
	for (int i = 0; i<N; i++)
		for (int j = 0; j<M; j++)
			tempMap[i][j] = map[i][j];
	printf("Y = a * sin (b*x)\n\n");
	printf("Which direction do you want to shoot?1-Left,2-Right  ");
	scanf("%d", &direct);
	if (direct == 1)
		direct = -1;
	else
		direct = 1;
	printf("Please enter a,b  \n");
	scanf("%d%d", &a, &b);
	/*double radian = angel / 180 * M_PI; // convert to radian
	//double radian = tan(angel);
	tempX = tank->x;
	tempY = tank->y;
	for (int i = 1; i <= power; i++)
	{
	if (angel < 90)
	{
	tempX = tempX - radian;
	tempY = tempY + 1;
	}
	else if (angel > 90 && angel < 180)
	{
	tempX = tempX - radian;
	tempY = tempY - 1;
	}
	else if (angel > 180 && angel < 270)
	{
	tempX = tempX + radian;
	tempY = tempY - 1;
	}
	else if (angel > 270 && angel < 360)
	{
	tempX = tempX + radian;
	tempY = tempY + 1;
	}
	else if (angel == 0 || angel == 360)
	tempY = tempY + 1;
	else if (angel == 90)
	tempX = tempX - radian;
	else if (angel == 180)
	tempY = tempY - 1;
	else if (angel == 270)
	tempX = tempX + radian;*/
	x = tank->x;
	y = tank->y;
	My_NewPI = My_NewPI / b; // sin cycle
	if (My_NewPI % 2 == 0)
		My_NewPI++;
	max = (My_NewPI / 2) + 1;
	angel = a / max;
	while (tempMap[(int)x][y] == ' ' || tempMap[(int)x][y] == tank->name || tempMap[(int)x][y] == '*' && (x > 0 && x < N - 1 && y>0 && y < M - 1))
	{

		//tempMap[(int)x + a][y + max] = '*';

		for (int i = 0; i < max; i++)
		{
			x = round(x - angel);
			y = y + direct;

			//i = hit(tank, map, arr, (int)x, (int)y, i, max, tempMap);
			if (map[(int)x][y] == 'A' || map[(int)x][y] == 'B' || map[(int)x][y] == 'C' || map[(int)x][y] == 'D')
			{
				switch (map[(int)x][y])
				{
				case 'A':
					arr[0]->life--;
					printf("HIT ! ! !\n");
					if (arr[0]->life == 0)
					{
						arr[0]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[0]->nameP);
						map[arr[0]->x][arr[0]->y] = ' ';
					}
					break;
				case 'B':
					arr[1]->life--;
					printf("HIT ! ! !\n");
					if (arr[1]->life == 0)
					{
						arr[1]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[1]->nameP);
						map[arr[1]->x][arr[1]->y] = ' ';
					}
					break;
				case 'C':
					arr[2]->life--;
					printf("HIT ! ! !\n");
					if (arr[2]->life == 0)
					{
						arr[2]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[2]->nameP);
						map[arr[2]->x][arr[2]->y] = ' ';
					}
					break;
				case 'D':
					arr[3]->life--;
					printf("HIT ! ! !\n");
					if (arr[3]->life == 0)
					{
						arr[3]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[3]->nameP);
						map[arr[3]->x][arr[3]->y] = ' ';
					}
					break;
				}
			}
			else if (map[(int)x][y] == '|')
			{
				PrintBoard(tempMap);
				return;
			}
			else if (x > N - 1 || x < 0 || y <0 || y >M - 1)
			{
				PrintBoard(tempMap);
				return;
			}
			else if (map[(int)x][y] == 'A' || map[(int)x][y] == 'B' || map[(int)x][y] == 'C' || map[(int)x][y] == 'D')
			{
				tempMap[(int)x][y] = 'X';
				PrintBoard(tempMap);
				return;
			}
			else
				tempMap[(int)x][y] = '*';

		}
		for (int i = 0; i < max; i++)
		{
			y = y + direct;
			x = round(x + angel);

			if (map[(int)x][y] == 'A' || map[(int)x][y] == 'B' || map[(int)x][y] == 'C' || map[(int)x][y] == 'D')
			{
				switch (map[(int)x][y])
				{
				case 'A':
					arr[0]->life--;
					printf("HIT ! ! !\n");
					if (arr[0]->life == 0)
					{
						arr[0]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[0]->nameP);
						map[arr[0]->x][arr[0]->y] = ' ';
					}
					break;
				case 'B':
					arr[1]->life--;
					printf("HIT ! ! !\n");
					if (arr[1]->life == 0)
					{
						arr[1]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[1]->nameP);
						map[arr[1]->x][arr[1]->y] = ' ';
					}
					break;
				case 'C':
					arr[2]->life--;
					printf("HIT ! ! !\n");
					if (arr[2]->life == 0)
					{
						arr[2]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[2]->nameP);
						map[arr[2]->x][arr[2]->y] = ' ';
					}
					break;
				case 'D':
					arr[3]->life--;
					printf("HIT ! ! !\n");
					if (arr[3]->life == 0)
					{
						arr[3]->live = FALSE;
						globalcount--;
						printf("Player %s is dead.\n", arr[3]->nameP);
						map[arr[3]->x][arr[3]->y] = ' ';
					}
					break;
				}
			}
			if (map[(int)x][y] == '|')
			{
				PrintBoard(tempMap);
				return;
			}
			else if (x > N - 1 || x < 0 || y <0 || y >M - 1)
			{
				PrintBoard(tempMap);
				return;
			}
			else if (map[(int)x][y] == 'A' || map[(int)x][y] == 'B' || map[(int)x][y] == 'C' || map[(int)x][y] == 'D')
			{
				tempMap[(int)x][y] = 'X';

				PrintBoard(tempMap);
				return;

			}
			else
				tempMap[(int)x][y] = '*';

		}
		angel = angel*(-1);
	}

	/*
	//printf("\n");
	if (tempMap[tempX][(int)round(tempY)] == '|')
	i = power;
	else if (tempX > N - 1 || tempX < 0 || tempY <0 || tempY >M - 1)
	i = power;
	else if (tempMap[tempX][(int)round(tempY)] == 'A' || tempMap[tempX][(int)round(tempY)] == 'B' || tempMap[tempX][(int)round(tempY)] == 'C' || tempMap[tempX][(int)round(tempY)] == 'D')
	{
	tempMap[tempX][(int)round(tempY)] = 'X';
	i = power;
	}
	else
	tempMap[tempX][(int)round(tempY)] = '*'; //print 1 shot
	}
	//tempY = round(tempY); // final Y index.*/
	PrintBoard(tempMap);
}