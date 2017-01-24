#include <curses.h>
#include <windows.h>

void init(void);

struct coordinates
{
    int y;
    int x;
};

int main()
{
    int max_y       = 0, max_x = 0;
    int next_x      = 0;
    int next_y      = 0;
    int direction_x = 3;            // Скорость изменения направления по X
    int direction_y = 1;            // Скорость изменения направления по Y
    int score       = 0;            // Счет
    int c;                          // Переменная хранения ввода с клавиатуры

    struct coordinates racket;
    struct coordinates ball;
    ball.y   = 0;
    ball.x   = 0;
    racket.y = 0;
    racket.x = 0;

    init();

    getmaxyx(stdscr, max_y, max_x);

    while(1)
    {
        clear();
        mvprintw(ball.y, ball.x, "o");
        mvprintw(0, 10, "%d", score);

        // Управляем ракеткой
		switch(c = getch())
		{	case KEY_UP:
                racket.y -= 1;
				break;
			case KEY_DOWN:
				racket.y += 1;
				break;
			default:
				break;
		}

		// Рисуем ракетку
        mvaddch(racket.y, racket.x, ACS_BLOCK);
        mvaddch(racket.y + 1, racket.x, ACS_BLOCK);
        mvaddch(racket.y + 2, racket.x, ACS_BLOCK);
        mvaddch(racket.y + 3, racket.x, ACS_BLOCK);

        refresh();
        Sleep(100);

        // Определяем положение мячика
        next_x = ball.x + direction_x;
        next_y = ball.y + direction_y;

        // Если у одного из краев, то меняем направление
        if (next_x >= max_x || next_x < 0 )
        {
            direction_x *= -1;
            score += 1;
            MessageBeep(MB_ICONEXCLAMATION);
        }

        if (next_y >= max_y || next_y < 0)
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
}
