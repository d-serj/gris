#include <stdlib.h>
#include <curses.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_SPACE 32

int main()
{
    int ch = 1;
    int x, y, row, col, c;
    char a;

    initscr();
    noecho();

    getmaxyx(stdscr, row, col);

    x = y = 0;

    printw ("simple text, when read this, please smiling:)");
    move(x, y);

    while (1)
    {
        c = getch();

        if (c == KEY_S && y <= row - 2)
            move(++y, x);


        else if (c == KEY_W && y > 0)
            move(--y, x);

        else if (c == KEY_A && x > 0)
            move(y, --x);

        else if (c == KEY_D && x <= col - 2)
            move(y, ++x);

        if (c == KEY_D && c == KEY_W)
            move(--y, --x);

        if (c == KEY_SPACE)
        {
            a = inch();

            if (a == 's' && ch == 1)
            {
                addch(a | A_BLINK);
                ch = !ch;
            }
            else if (a == 's' && ch == 0)
            {
                addch(a);
                ch = !ch;
            }

        }
        mvprintw(row-2, 0,"Row: %d| Colum: %d\n", x, y);
        move(y, x);
    }

    getch();
    endwin();

    return 0;
}
