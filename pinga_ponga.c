#include <curses.h>
#include <windows.h>

#define KEY_W 119
#define KEY_S 115

void init(void);
void racket(int, int);

struct coordinates
{
    int y;
    int x;
};

struct coordinates ball, racket_1, racket_2;

int main()
{
    int max_y       = 0, max_x = 0;
    int next_x      = 0;
    int next_y      = 0;
    int direction_x = 2;            // Скорость изменения направления по X
    int direction_y = 1;            // Скорость изменения направления по Y
    int score1      = 0;            // Счет игрока 1
    int score2      = 0;            // Счет игрока 2

    init();
    getmaxyx(stdscr, max_y, max_x); // Получаем максимальные величины X и Y

    ball.y     = 0;
    ball.x     = max_x / 2;
    racket_1.y = 0;
    racket_1.x = 0;
    racket_2.y = 0;
    racket_2.x = max_x - 1;

    for (;;)
    {
        clear();
        mvprintw(0, 20, "%2d", score1);
        mvprintw(0, 45, "%2d", score2);

        mvaddch(ball.y, ball.x, ACS_BULLET);

        racket(max_x, max_y);

        refresh();
        Sleep(80);

        // Определяем положение мячика
        next_x = ball.x + direction_x;
        next_y = ball.y + direction_y;

        // Если у одного из краев, то меняем направление
        if (next_x >= max_x || next_x < 0 )
        {
            direction_x *= -1;
            MessageBeep(MB_ICONEXCLAMATION);
        }

        if (next_y == max_y || next_y < 0)
        {
            direction_y *= -1;
            MessageBeep(MB_ICONEXCLAMATION);
        }

        // Иначе просто двигаем мячик
        else
        {
            ball.x += direction_x;
            ball.y += direction_y;
        }

        // Если мячик не попал на ракетку увеличивает счет игрока 1
        if (ball.x == 0 && !(ball.y >= racket_1.y && ball.y <= racket_1.y + 4))
            score1 += 1;

        else if (ball.x == max_x - 2 && !(ball.y >= racket_2.y && ball.y <= racket_2.y + 4))
            score2 += 1;

    }
    endwin();
}

void init(void)
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mvprintw(1, 0, ".---.  _                     .---.                        ");
    mvprintw(2, 0, ": .; ::_;                    : .; :                       ");
    mvprintw(3, 0, ":  _.'.-.,-.,-. .--.  .--.   :  _.'.--. ,-.,-. .--.  .--. ");
    mvprintw(4, 0, ": :   : :: ,. :' .; :' .; :  : :  ' .; :: ,. :' .; :' .; :");
    mvprintw(5, 0, ":_;   :_;:_;:_;`._. ;`.__.'  :_;  `.__.':_;:_;`._. ;`.__.'");
    mvprintw(6, 0, "                .-. :                          .-. :      ");
    mvprintw(7, 0, "                `._.'                          `._.'      ");
    refresh();
    system("pause");
}

void racket(int screenMax_x, int screenMax_y)
{
    int i;
    int c;  // Переменная хранения ввода с клавиатуры

    // Рисуем ракетки
    for (i = 0; i <= 4; ++i)
    {
        mvaddch(racket_1.y + i, racket_1.x, ACS_BLOCK);
        mvaddch(racket_2.y + i, racket_2.x, ACS_BLOCK);
    }

    // Управляем ракеткой
    switch(c = getch())
    {

    case KEY_UP:
        if (racket_2.y > 0)
            racket_2.y -= 2;
        break;

    case KEY_W:
        if (racket_1.y > 0)
            racket_1.y -= 2;
        break;

    case KEY_DOWN:
        if (racket_2.y <= screenMax_y - 6)
            racket_2.y += 2;
        break;

    case KEY_S:
        if (racket_1.y <= screenMax_y - 6)
            racket_1.y += 2;
    }
}
