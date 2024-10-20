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

#define MAX_SNAKE_LENGTH 100

typedef struct tail_t
{
    int x;
    int y;

} tail_t;

typedef struct snake_t
{
    int x;
    int y;
    struct tail_t *tail;
    size_t  tsize;
    char direction;
} snake_t;

//--> x

// || y

// \/

//@**

typedef struct food_t
{
    int x;
    int y;    
    int isEaten;
} food_t;

struct snake_t initSnake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.direction = LEFT;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * MAX_SNAKE_LENGTH);
    for (int i = 0; i < tsize; ++i)

    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
	snake.direction = LEFT;
    return snake;
}

struct food_t initFood()
{
    struct food_t food;
    food.x = rand() % 15;
    food.y = rand() % 15;    
    food.isEaten = 0;
    return food;
}




void printSnakeFood(struct snake_t snake,
					struct snake_t snake1,
 					struct food_t food,
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

    

    matrix[food.x][food.y] = '#';   
	matrix[snake.x][snake.y] = '@';
	matrix[snake1.x][snake1.y] = '%';
	
	if (p==1) // if the number of players is 1 we do not print snake1 but we should have the structure of snake1
	{
		matrix[snake1.x][snake1.y] = ' ';
		snake1.tsize = 0;
	}
    
  

    for (int i = 0; i < snake.tsize; ++i)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    }
    
    for (int i = 0; i < snake1.tsize; ++i)

    {
        matrix[snake1.tail[i].x][snake1.tail[i].y] = '+';
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

snake_t moveLeft(snake_t snake)
{
    for (int i = snake.tsize; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x = snake.x - 1;
    if (snake.x < 0)
    {
        snake.x = MAX_X - 1;
    }
    return snake;
}

snake_t moveRight(snake_t snake)
{
    for (int i = snake.tsize; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x = snake.x + 1;
    if (snake.x > MAX_X)
    {
        snake.x = 0 + 1;
    }
    return snake;
}

snake_t moveUp(snake_t snake)
{
    for (int i = snake.tsize; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.y = snake.y - 1;
    if (snake.y < 0)
    {
        snake.y = MAX_Y - 1;
    }
    return snake;
}

snake_t moveDown(snake_t snake)
{
    for (int i = snake.tsize; i > 0; i--)
    {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.y = snake.y + 1;
    if (snake.y > MAX_Y)
    {
        snake.y = 0 + 1;
    }
    return snake;
}

snake_t snakeMotion(snake_t snake, food_t food)
{
    switch (snake.direction)
    {
    case LEFT:
        return moveLeft(snake);
    case RIGHT:
        return moveRight(snake);
    case UP:
        return moveUp(snake);
    case DOWN:
        return moveDown(snake);
    }
    return snake;
    
}

snake_t changeDirection(snake_t snake, snake_t snake1, char ch)
{
    switch (ch)
    {
    case 'W':
    case 'w':
    {
        if (snake.direction != DOWN)
            snake.direction = UP;
        break;
    }

    case 'A':
    case 'a':
    {
        if (snake.direction != RIGHT)
            snake.direction = LEFT;
        break;
    }

    case 's':
    case 'S':
    {
        if (snake.direction != UP)
            snake.direction = DOWN;
        break;
    }

    case 'D':
    case 'd':
    {
        if (snake.direction != LEFT)
            snake.direction = RIGHT;
        break;
    }
    }
    
    return snake;
}

void generateSnakeDirection(snake_t *snake, food_t food)
{
	if ((snake->direction == LEFT || snake->direction == RIGHT) && snake->y == food.y)
	{
		return;
		}
	
	if ((snake->direction == LEFT || snake->direction == RIGHT) && snake->y != food.y)
	{
		if (food.x == snake->x)
	{
		if (abs(food.y - snake->y)<=MAX_Y/2)
		{
			snake->direction = food.y - snake->y>0? DOWN: UP;
		}
		else
		{
			snake->direction = food.y - snake->y>0? UP: DOWN;
		}
	}
	return;	
   }
		
		
	if ((snake->direction == UP || snake->direction == DOWN) && snake->x == food.x)
	{
		return;
		}
		
		if ((snake->direction == UP || snake->direction == DOWN) && snake->x != food.x)
	{
		if (food.y == snake->y)
	{
		if (abs(food.x - snake->x)<=MAX_X/2)
		{
			snake->direction = food.x - snake->x>0? RIGHT: LEFT;
		}
		else
		{
			snake->direction = food.x - snake->x>0? LEFT: RIGHT;
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
    struct snake_t snake = initSnake(10, 5, 2);
    struct snake_t snake1 = initSnake(7, 4, 2);
    food_t food = initFood();
    printSnakeFood(snake, snake1, food, p);
    
    if (p==1)
    {
    	snake1.x = 0;
    	snake1.y = 0;
    	snake1.tsize = 0;
    	}
    char c;
	
    while (1)
 	{
 		
        if (kbhit())
        {
            c = getch();
            snake = changeDirection(snake, snake1, c);
        }
        
        snake = snakeMotion(snake, food);
        if (p==2){
		
        snake1 = snakeMotion(snake1, food);
        generateSnakeDirection(&snake1, food);
    	}

        if ((snake.x == food.x) && (snake.y == food.y))
        {
			food = initFood();
			snake.tsize = snake.tsize+1;			
        }
        else if ((snake.tail[0].x == food.x) && (snake.tail[0].y == food.y))
        {
            food = initFood();
        }
        
        if ((snake1.x == food.x) && (snake1.y == food.y))
        {
			food = initFood();
			snake1.tsize = snake1.tsize+1;			
        }
        else if ((snake1.tail[0].x == food.x) && (snake1.tail[0].y == food.y))
        {
            food = initFood();
        }
        
        

        printSnakeFood(snake, snake1, food, p);
		
		if (food.isEaten)
		{
			food = initFood();
		}
		sleep(1);
        system("cls");
    }
    
}

else 
printf("Unfortunately, you have chosen the wrong number of players.\n Please try to choose 1 or 2 players next time.");
return 0;
}