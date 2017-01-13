#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <curses.h>

#define W 119
#define A 97
#define S 115
#define D 100


int main()
{
    int x, y, row, col, c;

    initscr();
    noecho();

    getmaxyx(stdscr, row, col);

    x = y = 0;

    printw ("simple text");
    move(x, y);

    while (1)
    {
        c = getch();

        if (c == S && y <= row - 2)
            move(++y, x);


        if (c == W && y > 0)
            move(--y, x);

        if (c == A && x > 0)
            move(y, --x);

        if (c == D && x <= col - 2)
            move(y, ++x);

        if (c == 32)
        {
            move(10, 10);
            //printf ("%d", getconsoletext());
        }
    }

    getch();
    endwin();

    return 0;
}
