#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include "windows.h"
#include <windows.h>

#define MAX_X 15

#define MAX_Y 15

#define UP 1

#define LEFT 2

#define RIGHT 3

#define DOWN 4

#define MAX_DRONE_LENGTH 100

typedef struct tail_t
{
    int x;
    int y;

} tail_t;

typedef struct drone_t
{
    int x;
    int y;
    struct tail_t *tail;
    size_t  tsize;
    char direction;
} drone_t;

//--> x

// || y

// \/

//@**

typedef struct pumpkin_t
{
    int x;
    int y;    
    int isTaken;
    int whatColor;
} pumpkin_t;

struct drone_t initDrone(int x, int y, size_t tsize)
{
    struct drone_t drone;
    drone.direction = LEFT;
    drone.x = x;
    drone.y = y;
    drone.tsize = tsize;
    drone.tail = (tail_t *)malloc(sizeof(tail_t) * MAX_DRONE_LENGTH);
    for (int i = 0; i < tsize; ++i)

    {
        drone.tail[i].x = x + i + 1;
        drone.tail[i].y = y;
    }
	drone.direction = LEFT;
    return drone;
}

struct pumpkin_t initPumpkin(int x, int y)
{
    struct pumpkin_t pumpkin;
    pumpkin.x = x;
    pumpkin.y = y;    
    pumpkin.isTaken = 0;
    pumpkin.whatColor = 'GREEN';
    return pumpkin;
}




void printDronePumpkin(struct drone_t drone,
					struct drone_t drone1,
 					struct pumpkin_t pumpkin,
					int p)

{

    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            matrix[i][j] = ' ';
        }
    } 

    for (pumpkin.x = 1; pumpkin.x < MAX_X; pumpkin.x=pumpkin.x + 2)
        for (pumpkin.y = 1; pumpkin.y < MAX_Y; pumpkin.y=pumpkin.y + 2)
        {
            matrix[pumpkin.x][pumpkin.y] = 'w';
        }
  
       
    
	matrix[drone.x][drone.y] = 'x';
	
	
	if (p==2) // if the number of players is 1 we do not print snake1 but we should have the structure of snake1
	{
        matrix[drone1.x][drone1.y] = '+';
		    for (int i = 0; i < drone1.tsize; ++i)
            {
                matrix[drone1.tail[i].x][drone1.tail[i].y] = 'a';
            }
	}
    
  

    for (int i = 0; i < drone.tsize; ++i)
    {
        matrix[drone.tail[i].x][drone.tail[i].y] = 'o';
    }
    
    for (int j = 0; j < MAX_Y; ++j)

    {
        for (int i = 0; i < MAX_X; ++i)
        {    
            printf("%c", matrix[i][j]);
        }

        printf("\n");
    }
}

drone_t moveLeft(drone_t drone)
{
    for (int i = drone.tsize; i > 0; i--)
    {
        drone.tail[i] = drone.tail[i - 1];
    }
    drone.tail[0].x = drone.x;
    drone.tail[0].y = drone.y;
    drone.x = drone.x - 1;
    if (drone.x < 0)
    {
        drone.x = MAX_X - 1;
    }
    return drone;
}

drone_t moveRight(drone_t drone)
{
    for (int i = drone.tsize; i > 0; i--)
    {
        drone.tail[i] = drone.tail[i - 1];
    }
    drone.tail[0].x = drone.x;
    drone.tail[0].y = drone.y;
    drone.x = drone.x + 1;
    if (drone.x > MAX_X)
    {
        drone.x = 0 + 1;
    }
    return drone;
}

drone_t moveUp(drone_t drone)
{
    for (int i = drone.tsize; i > 0; i--)
    {
        drone.tail[i] = drone.tail[i - 1];
    }
    drone.tail[0].x = drone.x;
    drone.tail[0].y = drone.y;
    drone.y = drone.y - 1;
    if (drone.y < 0)
    {
        drone.y = MAX_Y - 1;
    }
    return drone;
}

drone_t moveDown(drone_t drone)
{
    for (int i = drone.tsize; i > 0; i--)
    {
        drone.tail[i] = drone.tail[i - 1];
    }
    drone.tail[0].x = drone.x;
    drone.tail[0].y = drone.y;
    drone.y = drone.y + 1;
    if (drone.y > MAX_Y)
    {
        drone.y = 0 + 1;
    }
    return drone;
}

drone_t droneMotion(drone_t drone, pumpkin_t pumpkin)
{
    switch (drone.direction)
    {
    case LEFT:
        return moveLeft(drone);
    case RIGHT:
        return moveRight(drone);
    case UP:
        return moveUp(drone);
    case DOWN:
        return moveDown(drone);
    }
    return drone;
    
}

drone_t changeDirection(drone_t drone, drone_t drone1, char ch)
{
    switch (ch)
    {
    case 'W':
    case 'w':
    {
        if (drone.direction != DOWN)
            drone.direction = UP;
        break;
    }

    case 'A':
    case 'a':
    {
        if (drone.direction != RIGHT)
            drone.direction = LEFT;
        break;
    }

    case 's':
    case 'S':
    {
        if (drone.direction != UP)
            drone.direction = DOWN;
        break;
    }

    case 'D':
    case 'd':
    {
        if (drone.direction != LEFT)
            drone.direction = RIGHT;
        break;
    }
    }
    
    return drone;
}

void generateDroneDirection(drone_t *drone, pumpkin_t pumpkin)
{
	if ((drone->direction == LEFT || drone->direction == RIGHT) && drone->y == pumpkin.y)
	{
		return;
		}
	
	if ((drone->direction == LEFT || drone->direction == RIGHT) && drone->y != pumpkin.y)
	{
		if (pumpkin.x == drone->x)
	{
		if (abs(pumpkin.y - drone->y)<=MAX_Y/2)
		{
			drone->direction = pumpkin.y - drone->y>0? DOWN: UP;
		}
		else
		{
			drone->direction = pumpkin.y - drone->y>0? UP: DOWN;
		}
	}
	return;	
   }
		
		
	if ((drone->direction == UP || drone->direction == DOWN) && drone->x == pumpkin.x)
	{
		return;
		}
		
		if ((drone->direction == UP || drone->direction == DOWN) && drone->x != pumpkin.x)
	{
		if (pumpkin.y == drone->y)
	{
		if (abs(pumpkin.x - drone->x)<=MAX_X/2)
		{
			drone->direction = pumpkin.x - drone->x>0? RIGHT: LEFT;
		}
		else
		{
			drone->direction = pumpkin.x - drone->x>0? LEFT: RIGHT;
		}
	
		}
		return;
		}
	}

int main()
{	
	int p;
	printf("Hello, dear friend!\nChoose the number of players - 1 or 2:\n");
 	scanf("%d", &p);  
	if (p > 0 && p < 3)
	{	
    struct drone_t drone = initDrone(10, 5, 0);
    struct drone_t drone1 = initDrone(7, 4, 0);
    pumpkin_t pumpkin = initPumpkin(1, 1);

    printDronePumpkin(drone, drone1, pumpkin, p);
    
    if (p==1)
    {
    	drone1.x = NULL;
    	drone1.y = NULL;
    	drone1.tsize = NULL;
    	}
    char c;
	
    while (1)
 	{
 		
        if (kbhit())
        {
            c = getch();
            drone = changeDirection(drone, drone1, c);
        }
        
        drone = droneMotion(drone, pumpkin);
        if (p==2){
		
        drone1 = droneMotion(drone1, pumpkin);
        generateDroneDirection(&drone1, pumpkin);
    	}

        if ((drone.x == pumpkin.x) && (drone.y == pumpkin.y))
        {
			//pumpkin = initPumpkin();
			drone.tsize = drone.tsize+1;			
        }
        else if ((drone.tail[0].x == pumpkin.x) && (drone.tail[0].y == pumpkin.y))
        {
            //pumpkin = initPumpkin();
        }
        
        if ((drone1.x == pumpkin.x) && (drone1.y == pumpkin.y))
        {
			//pumpkin = initPumpkin();
			drone1.tsize = drone1.tsize+1;			
        }
        else if ((drone1.tail[0].x == pumpkin.x) && (drone1.tail[0].y == pumpkin.y))
        {
            //pumpkin = initPumpkin();
        }
        
        

        printDronePumpkin(drone, drone1, pumpkin, p);
		
		if (pumpkin.isTaken)
		{			
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		}
		sleep(1);
        system("cls");
    }
    
}

else 
printf("Unfortunately, you have chosen the wrong number of players.\n Please try to choose 1 or 2 players next time.");
return 0;
}