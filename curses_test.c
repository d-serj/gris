#include <stdlib.h>
#include <curses.h>

#define W 119
#define A 97
#define S 115
#define D 100


int main()
{
    int x, y, row, col, c;
    char a;

    initscr();
    noecho();

    getmaxyx(stdscr, row, col);

    x = y = 0;

    printw ("simple text, when read this? please smiling:)");
    move(x, y);

    while (1)
    {
        c = getch();

        if (c == S && y <= row - 2)
            move(++y, x);


        else if (c == W && y > 0)
            move(--y, x);

        else if (c == A && x > 0)
            move(y, --x);

        else if (c == D && x <= col - 2)
            move(y, ++x);

        if (c == D && c == W)
            move(--y, --x);

        if (c == 32)
        {
            a = inch();

            if (a == 's')
                mvprintw (5, 5, "Success");
            else
                mvprintw (5, 5, "ERROR  ");
        }
        mvprintw(row-2,0,"Row: %d| Colum: %d\n",x,y);
        move(y, x);
    }

    getch();
    endwin();

    return 0;
}
