#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define RED 4
#define WHITE 7

char *rus (char *p)
{
    static char txt[1024];

    CharToOemA (p, txt);
    return txt;
}

void gotoxy (int x, int y)
{
    COORD position = {x, y}; //позиция x и y
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, position);
}

void setcolor (int i)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, i);
}

void print_calendar (int month, int year, int horizontal, int vertical);

char *name[] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};

int main()
{
    int  i, y, month, year, horizontal, vertical;

    system ("mode 70, 40");

    for (;;)
    {
        printf (rus ("Введите год: "));
        scanf ("%d", &year);

        if (year < 1582 || year > 9999)
        {
            system ("cls");
            continue;
        }

        horizontal = 1;
        vertical   = 2;
        month      = 1;

        // Выводим на экран календарь с 3 месяцами в строке и 4 столбцами
        for (i = 1; i <= 4; ++i)
        {
            // Выводим 3 месяца в строку
            for (y = 1; y <= 3; ++y)
            {
                print_calendar (month, year, horizontal, vertical);
                ++month;
                horizontal += 23;
            }

            // Переходим на новую строку печати 3 месяцев
            horizontal = 1;
            vertical  += 9;
        }
        gotoxy(1, 38);
        system ("pause");
        system ("cls");
    }
    return 0;
}

void print_calendar (int month, int year, int horizontal, int vertical)
{
    int  i, y, w, t, tempDay, temp1, day;
    int  days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    day = 1;

    // ((year%4 == 0 and year%100 != 0) or (year%400 == 0))
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        days_month[1] = 29;
    else
        days_month[1] = 28;

    if (month <= 2)
    {
        --year;
        day += 3;
    }
    // В какой день начинается месяц
    w = (day + year + year / 4 - year / 100 + year / 400 + (31 * month + 10) / 12) % 7;

    gotoxy (horizontal, vertical);
    vertical += 1;
    printf ("       ");
    printf (rus (name[month - 1]));
    gotoxy (horizontal, vertical);
    vertical += 1;
    printf (rus (" Пн Вт Ср Чт Пт Сб Вс\n"));
    gotoxy (horizontal, vertical);

    // Печатаем количество пробелов в зависимости от дня начала месяца
    for (i = 1; i <= w; ++i)
        printf("   ");

    // Печатаем календарь на месяц
    t = days_month[month - 1];
    for (i = 1; i <= t; ++i)
    {
        temp1 = i;
        if (month <= 2)
        {
            temp1 += 3;
            tempDay = (temp1 + year + year / 4 - year / 100 + year / 400 + (31 * month + 10) / 12) % 7;
        }
        else
            tempDay = (temp1 + year + year / 4 - year / 100 + year / 400 + (31 * month + 10) / 12) % 7;

        if ((month == 1 && i == 1) || (tempDay == 5 || tempDay == 6))
        {
            setcolor(RED);
            printf ("%3d", i);
        }

        else
        {
            setcolor(WHITE);
            printf ("%3d", i);
        }
        if ((i + w) % 7 == 0)
            gotoxy (horizontal, ++vertical);
    }
    setcolor(WHITE);
}
