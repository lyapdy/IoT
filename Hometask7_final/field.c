#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include "windows.h"
#include <windows.h>

#define MAX_X 15

#define MAX_Y 15

typedef struct field_t
{
    int x;
    int y;
    int isReal;
    int whatColor;
    size_t size;
} field_t;

struct field_t initField(size_t size)
{
    struct field_t field;
    field.size = size;
    return field;
}

void printField(struct field_t field)
{
char matrix[field.size][field.size];
    for (int i = 0; i < MAX_X; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            matrix[i][j] = ' ';
        }
    }

        for (field.x = 1; field.x < MAX_X; field.x=field.x + 2)
        for (field.y = 1; field.y < MAX_Y; field.y=field.y + 2)
        {            
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            matrix[field.x][field.y] = 'w';  
            //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // сброс цвета
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

int main()
{
    struct field_t field = initField(15);
    printField(field);
    return 0;
}