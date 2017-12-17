#include <math.h>
DirectShot(Tank *tank,char map[N][M])
{
    int angel,power;
    double tempY;
    printf("Enter Angel and Power:\n");
    scanf("%d%d",&angel,&power);
    angel=angel/180 * math.pi;
    double radian=tan(double angel);
    tempY=tank->y;
    for(int i=1;i<=power;i++)
    {
    tank->x=tank->x+1;
    tempY=tempY+radian;
    }

    if(tempY%1>0.5)
        tempY=(int)tempY+1;
    else
        tempY=(int)tempY;
}
