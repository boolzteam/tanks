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
#define column 4
#define row 2
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
	int shotTable[row][column];

}Tank;
int globalcount = 0;
int prev_tank[5] = {0,0,0,0,0};  //0-tank index, 1-hit or not, 2-hitted tank, 3-x, 4-y
char password[5] = "1234";
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
bool glob_hit(Tank* tank, char map[N][M], Tank ** arr, int x, int y);
double make_a_positive(double);
void extractFile(Tank**Arr, char* AdminID,int players);
int check_two_nums(char num1, char num2, char[M]);

int main()
{

	//bool *test[7];
	int admin;
	char GameBoard[50][224],AdminID[M], play_char[M];
	BuildMap(GameBoard);
	PrintBoard(GameBoard);
	admin = check_two_nums('1', '0', "Admin accsess?1-Yes,0-No\n");
	if (admin == 1)
	{
		printf("Enter the admin ID \n");
		do {
			scanf("%s", &AdminID);
		} while (Test_ID(AdminID) == FALSE);
	}
	int players = 5;
	Tank ** Arr = NULL;
	getchar();
	while (1)//בדיקת קלט תקין
	{
		printf("Enter number of players\n");
		gets(play_char);
		if (play_char[0] != '2'&& play_char[0] != '3'&& play_char[0] != '4' || strlen(play_char)>1)
		{
			printf("Wrong Input,Try again!\n");
			continue;
		}
		else
		{
			players = play_char[0] - '0';
			break;
		}
	}
	Arr = initialize(players, GameBoard);
	PrintBoard(GameBoard);
	Play(GameBoard, Arr, players);
	if (admin == 1)
		extractFile(Arr, AdminID, players);
	for (int i = 0; i < players; i++) // free memory
		free(Arr[i]);
	free(Arr);
	for (int i = 0; i < 10; i++)
		printf("\ndid you change the STEPS?!??!?\nfrom 50 to 5\nfunction move....\n");
	return 0;
}
void extractFile(Tank**Arr, char* AdminID, int players)
{
	char temp[M];
	int tries = 4;
	do {
		tries--;
		printf("Please enter the admin ID, you have %d tries\n",tries);
		scanf("%s", &temp);
	} while (strcmp(AdminID, temp) && tries);
	if ((strcmp(AdminID, temp))) {
		printf("Wrong admin ID, failed to open file\n");
		return;
	}
	FILE *fout = NULL;
	if ((fout=fopen("Shoot_Data_Base.txt", "w")) == NULL)
	{
		printf("Error, failed opening file\n");
		exit(1);
	}
	fprintf(fout, "Shoot Table\n\n");
	for (int i = 0; i < players; i++)
	{
		if(Arr[i]->shotTable[0][0] != 0)
			fprintf(fout, "Name: %s\nID:%s\nDirect Shoot: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n", Arr[i]->nameP, Arr[i]->ID, Arr[i]->shotTable[0][0], Arr[i]->shotTable[1][0], Arr[i]->shotTable[0][0] - Arr[i]->shotTable[1][0], ((double)(Arr[i]->shotTable[1][0]) / (double)(Arr[i]->shotTable[0][0])) * 100);
		else
			fprintf(fout, "Name: %s\nID:%s\nDirect Shoot: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n", Arr[i]->nameP, Arr[i]->ID, Arr[i]->shotTable[0][0], Arr[i]->shotTable[1][0], Arr[i]->shotTable[0][0] - Arr[i]->shotTable[1][0],0);
		if (Arr[i]->shotTable[0][1] != 0)
			fprintf(fout, "Steep Path: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n", Arr[i]->shotTable[0][1], Arr[i]->shotTable[1][1], Arr[i]->shotTable[0][1] - Arr[i]->shotTable[1][1], ((double)(Arr[i]->shotTable[1][1]) / (double)(Arr[i]->shotTable[0][1])) * 100);
		else
			fprintf(fout, "Steep Path: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n", Arr[i]->shotTable[0][1], Arr[i]->shotTable[1][1], Arr[i]->shotTable[0][1] - Arr[i]->shotTable[1][1],0);
		if (Arr[i]->shotTable[0][2] != 0)
			fprintf(fout, "Guided Missle: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n", Arr[i]->shotTable[0][2], Arr[i]->shotTable[1][2], Arr[i]->shotTable[0][2] - Arr[i]->shotTable[1][2], ((double)(Arr[i]->shotTable[1][2]) / (double)(Arr[i]->shotTable[0][2])) * 100);
		else
			fprintf(fout, "Guided Missle: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n", Arr[i]->shotTable[0][2], Arr[i]->shotTable[1][2], Arr[i]->shotTable[0][2] - Arr[i]->shotTable[1][2], 0);
		if (Arr[i]->shotTable[0][3] != 0)
			fprintf(fout, "Crazy Sheep: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n\n", Arr[i]->shotTable[0][3], Arr[i]->shotTable[1][3], Arr[i]->shotTable[0][3] - Arr[i]->shotTable[1][3], ((double)(Arr[i]->shotTable[1][3]) / (double)(Arr[i]->shotTable[0][3])) * 100);
		else
			fprintf(fout, "Crazy Sheep: %d\tHits:%d\tMiss:%d,(%.02lf%%)\n\n", Arr[i]->shotTable[0][3], Arr[i]->shotTable[1][3], Arr[i]->shotTable[0][3] - Arr[i]->shotTable[1][3], 0);
	}
	printf("Dear Admin,The file is ready.\n");
	fclose(fout);
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
		for (int k = 0; k < 2; k++)
			for (int l = 0; l < 4; l++)
				Arr[i]->shotTable[k][l] = 0;
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
	char guide[M], str[M];
	globalcount = players;
	int choose,tries=4,guide_flag=0;
	choose = check_two_nums('1', '0', "Guide access? 1-Yes, 0-No\t");
	//printf("Guide access? 1-Yes  0-No\n");
	//scanf("%d", &choose);
	if (choose)
	{
		do {
			tries--;
			printf("Please enter the guide password, you have %d tries\n", tries);
			scanf("%s", &guide);
		} while (strcmp(password, guide) && tries);
		if ((strcmp(password, guide)))
			printf("Wrong password, guide has no access\n");
		else
		{
			printf("Guide has an access\n");
			guide_flag = 1;
		}
	}
	while (globalcount > 1)
	{
		for (int i = 0; i < players; i++)
			if (Arr[i]->live == TRUE)
			{
				prev_tank[3] = Arr[i]->x;
				prev_tank[4] = Arr[i]->y;
				prev_tank[0] = i;
				printf("Its %s turn!\n", Arr[i]->nameP);
				choose = check_two_nums('1', '0', "would you like to move? 1-Yes, 0-No\t");
				if (choose)
					Move(Arr[i], Board);
				Shoot(Arr[i], Board, Arr);
				if (guide_flag)
				{
					choose = check_two_nums('1', '0', "Guide access, Do you want to try this turn again? 1-Yes, 0-No\t");
					//printf("? 1-Yes  0-No\n");
					//scanf("%d", &choose);
					if (choose)
					{

						Board[Arr[i]->x][Arr[i]->y] = ' ';
						Arr[i]->x = prev_tank[3];
						Arr[i]->y = prev_tank[4];
						Board[Arr[i]->x][Arr[i]->y] = Arr[i]->name;
						if (prev_tank[1])
						{
							Arr[prev_tank[2]]->life++;
							if (Arr[prev_tank[2]]->live == FALSE)
							{
								Arr[prev_tank[2]]->live == TRUE;
								Board[Arr[prev_tank[2]]->x][Arr[prev_tank[2]]->y] = Arr[prev_tank[2]]->name;
								globalcount++;
							}
						}
						i = (i - 1) % players;
						PrintBoard(Board);
					}
				}
			}
	}
	for (int i = 0; i < players; i++)
		if (Arr[i]->live == TRUE)
			printf("\nCongratulations %s You Won The Game!\n", Arr[i]->nameP);
}
void Move(Tank* tank, char Board[N][M])
{
	
	char str[M];
	PrintBoard(Board);
	int choose, step;
	Board[tank->x][tank->y] = ' ';
	choose = check_two_nums('2', '1', "What direction would you like to move? Left-1, Right-2\t");
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
		tank->shotTable[0][0]++;
		break;
	case 2:
		Steep_path(tank, Board, Arr);
		tank->shotTable[0][1]++;
		break;
	case 3:
		Guided_Missile(tank, Board);
		tank->shotTable[0][2]++;
		break;
	case 4:
		CrazySheep(tank, Board, Arr);
		tank->shotTable[0][3]++;
		break;
	}
}

void Directshot(Tank* tank, char map[N][M], Tank ** arr)
{
	int power = 0, index = 0,x;
	double angel = 0, tempY = 0,tempX = 0,radian ;
	char tempMap[N][M];
	for (int i = 0; i<N; i++)
		for (int j = 0; j<M; j++)
			tempMap[i][j] = map[i][j];

	printf("Enter Angel and Power:\n");
	scanf("%lf%d", &angel, &power);
	if (angel < 90)
		radian = angel / 180 * M_PI; // convert to 
	else
	{
		radian = (((int)angel % 90)* M_PI / 180);
	}
	tempX = tank->x;
	x = tank->x;
	tempY = tank->y;
	for (int i = 1; i <= power; i++)
	{
		if (angel < 90)
		{
			tempX = tempX - radian;
			x = (int)round(tempX);
			tempY = tempY + 1;
		}
		else if (angel > 90 && angel < 180)
		{
			tempX = tempX - radian;
			x = (int)round(tempX);
			tempY = tempY - 1;
		}
		else if (angel > 180 && angel < 270)
		{
			tempX = tempX + radian;
			x = (int)round(tempX);
			tempY = tempY - 1;
		}
		else if (angel > 270 && angel < 360)
		{
			tempX = tempX + radian;
			x = (int)round(tempX);
			tempY = tempY + 1;
		}
		else if (angel == 0 || angel == 360)
			tempY = tempY + 1;
		else if (angel == 90)
		{
			tempX = tempX - 1;
			x = (int)round(tempX);
		}
		else if (angel == 180)
			tempY = tempY - 1;
		else if (angel == 270)
		{
			tempX = tempX + 1;
			x = (int)round(tempX);
		}

		if (tempMap[x][(int)tempY] == '|' || x < 0 || x >= N || (int)tempY < 0 || (int)tempY >= M)
		{
			printf("break-point 1\n");
			break;
		}
		printf("x= %d\n tempx= %lf\n,tempY-%lf\n", x, tempX, tempY);
		if (glob_hit(tank, map, arr, x, (int)tempY) == FALSE)
			tempMap[x][(int)tempY] = '*';
		else {
			tank->shotTable[1][0]++;
			tempMap[x][(int)tempY] = 'X';
			break;
		}
	}
	PrintBoard(tempMap);
}

bool glob_hit(Tank* tank, char map[N][M], Tank ** arr, int x, int y) {
	int i;
	if ((map[x][y] == 'A' || map[x][y] == 'B' || map[x][y] == 'C' || map[x][y] == 'D') && map[x][y]!=tank->name)
	{
		switch (map[x][y])
		{
		case 'A':
			i = 0;
			prev_tank[2] = 0;
			break;
		case 'B':
			prev_tank[2] = 1;
			i = 1;
			break;
		case 'C':
			prev_tank[2] = 2;
			i = 2;
			break;
		case 'D':
			prev_tank[2] = 3;
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
		prev_tank[1] = 1;
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
				tank->shotTable[1][1]++;
				tempmap[j][temp_y] = 'X';
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
				tank->shotTable[1][1]++;
				tempmap[j][temp_y] = 'X';
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
			tank->shotTable[1][1]++;
			tempmap[x][real_y] = 'X';
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
	int power = 0, index = 0, a, b, My_NewPI = 28, y = 0, max, direct,k;
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
	x = tank->x;
	y = tank->y;
	if (b <= 2)
		b=3;
	My_NewPI = My_NewPI / b; // sin cycle
	if (My_NewPI % 2 == 0)
		My_NewPI++;
	max = (My_NewPI / 2) + 1;
	angel = a / max;
	while (tempMap[(int)x][y] == ' ' || tempMap[(int)x][y] == tank->name || tempMap[(int)x][y] == '*' && (x > 0 && x < N - 1 && y>0 && y < M - 1))
	{
		for (int i = 0; i < max; i++)
		{
			x = round(x - angel);
			y = y + direct;
		
			
			if (map[(int)x][y] == 'A' || map[(int)x][y] == 'B' || map[(int)x][y] == 'C' || map[(int)x][y] == 'D')
			{
				prev_tank[1] = 1;
				tank->shotTable[1][3]++;
				switch (map[(int)x][y])
				{
				case 'A':
					k = 0;
					prev_tank[2] = 0;
					break;
				case 'B':
					k = 1;
					prev_tank[2] = 1;
					break;
				case 'C':
					k = 2;
					prev_tank[2] = 2;
					break;
				case 'D':
					k = 3;
					prev_tank[2] = 3;
					break;
				default:
					break;
				}
				arr[k]->life--;
				printf("HIT ! ! !\n");
				if (arr[k]->life == 0)
				{
					arr[k]->live = FALSE;
					globalcount--;
					printf("Player %s is dead.\n", arr[k]->nameP);
					map[arr[k]->x][arr[k]->y] = ' ';
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
				prev_tank[1] = 1;
				tank->shotTable[1][3]++;
				switch (map[(int)x][y])
				{
				case 'A':
					k = 0;
					prev_tank[2] = 0;
					break;
				case 'B':
					k = 1;
					prev_tank[2] = 1;
					break;
				case 'C':
					k = 2;
					prev_tank[2] = 2;
					break;
				case 'D':
					k = 3;
					prev_tank[2] = 3;
					break;
				default:
					break;
				}
				arr[k]->life--;
				printf("HIT ! ! !\n");
				if (arr[k]->life == 0)
				{
					arr[k]->live = FALSE;
					globalcount--;
					printf("Player %s is dead.\n", arr[k]->nameP);
					map[arr[k]->x][arr[k]->y] = ' ';
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
	PrintBoard(tempMap);
}

int check_two_nums(char num1, char num2, char msg[M])
{
	char str[M];
	int choose;
	getchar();
	while (1)//בדיקת קלט תקין במחרוזת
	{
		
		printf("%s",msg);
		gets(str);
		if (str[0] !=  num1 && str[0] != num2 || strlen(str) > 1)
		{
			printf("Wrong Input,Try again!\n");
			continue;
		}
		else
		{
			choose = str[0] - '0';
			break;
		}
	}
	return choose;
}

