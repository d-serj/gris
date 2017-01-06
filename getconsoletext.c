#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define W 119
#define A 97
#define S 115
#define D 100

void gotoxy (int x, int y)
{
    COORD position = {x, y}; //позиция x и y
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, position);
}

int getconsoletext ()
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    // Получение координат:
    CONSOLE_SCREEN_BUFFER_INFO oBufInfo = {0};
    GetConsoleScreenBufferInfo(hCon, &oBufInfo);
    // oBufInfo.dwCursorPosition = 3,0

    // Получение атрибутов символа на месте курсора:
    WORD wAttrib = 0;
    DWORD dwReaden = 0;
    BOOL bOk = ReadConsoleOutputAttribute(hCon, &wAttrib, 1, oBufInfo.dwCursorPosition, &dwReaden);
    return wAttrib;
}

int main()
{
    int x, y, a;
    char c;

    x = y = 0;

    printf ("simple text");
    gotoxy(x, y);

    while (1)
    {
        c = getch();

        if (c == D && x <= 60)
            gotoxy(++x, y);

        if (c == A && x > 0)
            gotoxy(--x, y);

        if (c == S && y <= 20)
            gotoxy(x, ++y);

        if (c == W && y > 0)
            gotoxy(x, --y);

        if (c == 32)
        {
            gotoxy(10, 10);
            printf ("%d", getconsoletext());
        }
    }

    return 0;
}
