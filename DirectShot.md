#include <math.h>
DirectShot(Tank ** tank,char map[N][M],int index)
{
    int angel,power,tempX;
    
    char tempMap[N][M];    
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            tempMap[i][j]=map[i][j];
    
    double tempY;
    printf("Enter Angel and Power:\n");
    scanf("%d%d",&angel,&power);
    angel=angel/180 * math.pi; // convert to radian
    double radian=tan(double angel);
    tempX=tank[index]->x;
    tempY=tank[index]->y;
    for(int i=1;i<=power;i++)
    {
    tempX=tempX+1;
    tempY=tempY+radian;
    
    if(map[tempX][round(tempY)] == 'A' || map[tempX][round(tempY)] == 'B' || map[tempX][round(tempY)] == 'C' || map[tempX][round(tempY)] == 'D')
    {
        switch (map[tempX][round(tempY)]):
        case 'A':
            tank[0]->life--;
            if(life==0)
                tank[0]->live=FALSE;
         break;

    }
    tempMap[tempX][round(tempY)]='*'; //print 1 shot
    }
    tempY=round(tempY); // final Y index.
}

int round(double tempY) // round function
{
    if(tempY%1>0.5)
        return (int)tempY+1;
    else
        return(int)tempY;
 }

