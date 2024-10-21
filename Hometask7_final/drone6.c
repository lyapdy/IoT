#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include "windows.h"
#include <windows.h>
#include <locale.h>

#define MAX_X 15

#define MAX_Y 15

#define UP 1

#define LEFT 2

#define RIGHT 3

#define DOWN 4

#define MAX_DRONE_LENGTH 100


typedef struct tail_t // структура хвост
{
    int x;
    int y;

} tail_t;

typedef struct drone_t // структура дрон
{
    int x;
    int y;
    struct tail_t *tail;
    size_t  tsize;
    char direction;
} drone_t;

typedef struct pumpkin_t // структура тыква
{
    int x;
    int y;    
    int isTaken;   
    
} pumpkin_t;

typedef struct field_t // структура поле - отображает весь зеленый урожай
{
    int x;
    int y;
    int isReal;
    int isEmpty;
    int whatColor;
    size_t fsize;
} field_t;

struct drone_t initDrone(int x, int y, size_t tsize) // инициализируем дроны
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

struct field_t initField(size_t fsize) // поле заполн€етс€ урожаем - буквами w
{
    struct field_t field;
    field.fsize = fsize;
    return field;
}

struct pumpkin_t initPumpkin(x, y) // тыква зреет, зрела€ тыква отображаетс€ буквой r - ready - зрела€
{
    struct pumpkin_t pumpkin;

        pumpkin.x = x;
        pumpkin.y = y;
    
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
          
    pumpkin.isTaken = 0;
    return pumpkin;
}


void printDrone(struct drone_t drone,
					struct drone_t drone1,
                    struct drone_t drone2,
 					struct pumpkin_t pumpkin,
                    struct field_t field,
					int p)                  // рисуем дроны

{

    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            matrix[i][j] = ' ';
        }
    } 

    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hConsole, FOREGROUND_RED);    
    // matrix[pumpkin.x][pumpkin.y] = 'r'; 
	matrix[drone.x][drone.y] = 'x';


	if (p==2) // if the number of players is 1 we do not print snake2 but we should have the structure of snake1
	{
        matrix[drone1.x][drone1.y] = '+'; // голова второго дрона - +
		    for (int i = 0; i < drone1.tsize; ++i)
            {
                matrix[drone1.tail[i].x][drone1.tail[i].y] = 'a'; // тележки второго дрона - а
            }
	}

    if (p==3) // we print all snakes
	{
        matrix[drone1.x][drone1.y] = '+'; // голова второго дрона - +
		    for (int i = 0; i < drone1.tsize; ++i)
            {
                matrix[drone1.tail[i].x][drone1.tail[i].y] = 'a'; // тележки второго дрона - а
            }

        matrix[drone2.x][drone2.y] = 'y'; // голова третьего дрона - у
		    for (int i = 0; i < drone2.tsize; ++i)
            {
                matrix[drone2.tail[i].x][drone2.tail[i].y] = 'q'; // тележки второго дрона - q
            }    
	}

     for (field.x = 1; field.x < MAX_X; field.x=field.x + 2) // заполн€ем зеленым урожаем с одной спелой тыквой
        for (field.y = 1; field.y < MAX_Y; field.y=field.y + 2)
        {                        
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                matrix[field.x][field.y] = 'w'; // весть урожай
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // сброс цвета
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // хочу покрасить только спелую тыкву в красный цвет - не получаетс€ и зафиксировать до конца игры
                matrix[pumpkin.x][pumpkin.y] = 'r'; // только зрела€ тыква
                }
    
  

    for (int i = 0; i < drone.tsize; ++i)
    {
        matrix[drone.tail[i].x][drone.tail[i].y] = 'o'; // тележки у первого дрона - о
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

drone_t droneMotion(drone_t drone)
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

drone_t changeDirection(drone_t drone, drone_t drone1, drone_t drone2, char ch)
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

random_odd()
{
    int res;
    res = rand() % 14;
    if (res % 2 != 0)
        return res;
    else
        return res + 1;

}

int main()
{	
    setlocale(LC_ALL, "Rus");
	int p;
    int flag=1;
    int cnt=0;
    
   	printf("«дравствуйте!\n¬ыберите количество игроков - 1, 2 или 3:\n");
 	scanf("%d", &p);  
	if (p > 0 && p <= 3)
	{	
    struct drone_t drone = initDrone(10, 12, 0);
    struct drone_t drone1 = initDrone(7, 8, 0);
    struct drone_t drone2 = initDrone(11, 4, 0);
    pumpkin_t pumpkin = initPumpkin(random_odd(), random_odd());
    struct field_t field = initField(15);

    printDrone(drone, drone1, drone2, pumpkin, field, p);
    
    if (p==1)
    {
    	drone1.x = NULL;
    	drone1.y = NULL;
    	drone1.tsize = NULL;

        drone2.x = NULL;
    	drone2.y = NULL;
    	drone2.tsize = NULL;

    	}
    char c;
	
    while (flag==1)
 	{

        
 		
        if (kbhit())
        {
            c = getch();
            drone = changeDirection(drone, drone1, drone2, c);
        }
        
        drone = droneMotion(drone);

        if (p==2){
		
        drone1 = droneMotion(drone1);
        generateDroneDirection(&drone1, pumpkin);
    	}

        if (p==3){

        drone1 = droneMotion(drone1);
        generateDroneDirection(&drone1, pumpkin);
		
        drone2 = droneMotion(drone2);
        generateDroneDirection(&drone2, pumpkin);
    	}



        if ((drone.x == pumpkin.x) && (drone.y == pumpkin.y))
        {
			pumpkin = initPumpkin(random_odd(), random_odd());
			drone.tsize = drone.tsize+1;
            cnt++;			
        }
        else if ((drone.tail[0].x == pumpkin.x) && (drone.tail[0].y == pumpkin.y))
        {
            pumpkin = initPumpkin(random_odd(), random_odd());
        }
        
        if ((drone1.x == pumpkin.x) && (drone1.y == pumpkin.y))
        {
			pumpkin = initPumpkin(random_odd(), random_odd());
			drone1.tsize = drone1.tsize+1;	
            cnt++;
            		
        }
        else if ((drone1.tail[0].x == pumpkin.x) && (drone1.tail[0].y == pumpkin.y))
        {
            pumpkin = initPumpkin(random_odd(), random_odd());
        }


        if ((drone2.x == pumpkin.x) && (drone2.y == pumpkin.y))
        {
			pumpkin = initPumpkin(random_odd(), random_odd());
			drone2.tsize = drone2.tsize+1;
            cnt++;	
            		
        }
        else if ((drone2.tail[0].x == pumpkin.x) && (drone2.tail[0].y == pumpkin.y))
        {
            pumpkin = initPumpkin(random_odd(), random_odd());
        }
        
        

        printDrone(drone, drone1, drone2, pumpkin, field, p);

        for (int i = 0; i < drone.tsize; ++i)
        {
            if (drone.tail[i].x == drone.x && drone.tail[i].y == drone.y) // столкновение дрона с собой
            {flag = 0;
            printf(" онец игрыr\n");
            printf("%d\n", cnt);
            sleep(5);            
            }
        }    

		
		if (cnt == 1) // если все дроны собирают все тыквы - то мы выиграли!
		{			
            flag = 0;
            printf("¬ы выиграли! ѕоздавл€ем!\n");
            printf("%d\n", cnt);
            sleep(5);
		}
		sleep(1);
        system("cls");
    }
    
}

else 
printf("  сожалению, вы выбрали неправильное количество игроков.\n ѕопробуйте выбрать 1, 2 или 3 игрока в следующий раз.");
return 0;
}