#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#define N 50
#define M 224
void BuildMap(char map[N][M]);

int main() {
	
		char tempmap[N][M];
		double a, b, c, y,prev_y=0;
		BuildMap(tempmap);
		printf("Enter a b c\n");
		scanf("%lf%lf%lf", &a,&b,&c);
		int tankx = 40;
		int tanky = 198, dx,x,real_y,temp_y,direction=1;
		
		for (int i = 0; i + tanky < M; i++) //axel wide
		{

			dx = N - 1 - tankx;
			y = a*i*i + b*i;
			for (int j = N - 1 - dx - (int)round(prev_y); j > N - 1 - dx - (int)round(y); j--)//print up
			{
				if (direction == 2)
					temp_y = i - 1 + tanky;
				else
					temp_y = tanky - i;
				if (tempmap[j][temp_y] == '|' || j < 0 || j >= N || temp_y < 0 || temp_y >= M)
				{
					y = 1000;
					break;
				}
				tempmap[j][temp_y] = '*';
			}
			for (int j = N - dx - (int)round(prev_y); j < N - dx - (int)round(y); j++)//print down
			{
				printf("999");
				if (direction == 2)
					temp_y = i - 1 + tanky;
				else
					temp_y = tanky - i;
				if (tempmap[j][temp_y] == '|' || j < 0 || j >= N || temp_y < 0 || temp_y >= M)
				{
					printf("555");
					y = 1000;
					break;
				}
				tempmap[j][temp_y] = '*';
			}
			
			x = N - 1 - dx - (int)round(y);
			if (direction == 2)
				real_y = i + tanky;
			else
				real_y = tanky - i-1;
		
			if (y == 1000 || /*tempmap[x][real_y] == '|' ||*/ x < 0 || x >= N || real_y < 0 || real_y >= M ) 
				break;
			if (y > prev_y)
				tempmap[x][real_y] = '*';
			prev_y = y;
		}
		for (int i = 0; i<N; i++)
		{
			for (int j = 0; j < M; j++)
				printf("%c", tempmap[i][j]);
			printf("\n");
		}
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