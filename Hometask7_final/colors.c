#include <stdio.h>
#include <windows.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("��� ������� �����!\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ����� �����
    printf("� ��� ����������\n");
    return 0;
}