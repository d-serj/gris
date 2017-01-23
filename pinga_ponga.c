#include <curses.h>
#include <windows.h>

#define DELAY 30000

int main()
{
    int x = 0, y = 0;
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int next_y = 0;
    int direction_x = 2;
    int direction_y = 1;

    initscr();
    noecho();
    curs_set(FALSE);

    getmaxyx(stdscr, max_y, max_x);
    nodelay(stdscr, TRUE);

    while(1)
    {
        clear();
        mvprintw(y, x, "o");
        refresh();
        Sleep(10);

        next_x = x + direction_x;
        next_y = y + direction_y;

        if (next_x >= max_x || next_x < 0 )
        {
            direction_x *= -1;
            MessageBeep(MB_ICONEXCLAMATION);
        }

        if (next_y >= max_y || next_y < 0)
        {
            direction_y *= -1;
            MessageBeep(MB_ICONEXCLAMATION);
        }

        else
        {
            x += direction_x;
            y += direction_y;
        }
    }

    endwin();
}
