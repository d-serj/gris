#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BACKGROUND 39
#define BACKGROUNDRED 36
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
//int celebrate (int year, int month, int day);
void pasha_p (int year, int couter);

char *name[] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
int  *days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                               //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
int *celebrateDays[12][31] = {  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Январь
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Февраль
                                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Март
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Апрель
                                {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Май
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // Июнь
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Июль
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Август
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Сентябрь
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Октябрь
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Ноябрь
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Декабрь
                            };
int main()
{
    int  i, y, month, year, horizontal, vertical, counter;

    system ("mode 70, 40");

    for (;;)
    {
        counter = 0;  // Счетчик начала цикла

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

        pasha_p(year, counter);

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

        counter = 1;            // Счетчик конца цикла
        pasha_p(year, counter); // Сбрасываем дату Пасхи и Троицы

        gotoxy(1, 38);
        system ("pause");
        system ("cls");
    }
    return 0;
}

void print_calendar (int month, int year, int horizontal, int vertical)
{
    int  i, y, w, t, tempDay, temp1, day;


    day = 1;

    // Определяем високосный год ((year%4 == 0 and year%100 != 0) or (year%400 == 0))
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

        // Если день праздничный в субботу или воскресенье, то подсвечиваем их
        if (celebrateDays[month - 1][i - 1] == 1 && (tempDay == 5 || tempDay == 6))
        {
            setcolor(BACKGROUNDRED);
            printf ("%3d", i);
        }

        // Если день суббота или воскресенье, то подсвечиваем под ними фон
        else if (tempDay == 5 || tempDay == 6)
        {
            setcolor(BACKGROUND);
            printf ("%3d", i);
        }

        // Если день праздничный, то выделяем его красным
        else if (celebrateDays[month - 1][i - 1] == 1)
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

void pasha_p (int year, int counter)
{
    int a, b, c, d, e, temp1, temp2, temp3, tempMonth;

    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = (19 * a + 15) % 30;
    e = (2 * b + 4 * c + 6 * d + 6) % 7;

    temp1 = (d + e - 9) - 1;
    if (temp1 + 13 > 29)
    {
        celebrateDays[4][temp1 + 13 - 30] = 1;
        temp3 = temp1 + 13 - 30 + 50;
        temp2 = days_month[4];
        temp3 = temp3 - temp2;
        celebrateDays[5][temp3 - 1] = 1;
    }
    else
    {
        celebrateDays[3][temp1 + 13] = 1;
        temp3 = temp1 + 13 + 50;
        temp2 = days_month[3];
        temp3 = temp3 - temp2;
        if (temp3 - temp2 > 31)
        {
            tempMonth = 5;
            celebrateDays[tempMonth][temp3 - 1] = 1;
        }
        else
        {
            tempMonth = 4;
            celebrateDays[tempMonth][temp3 - 1] = 1;
        }
    }

    // Сбрасываем даты Пасхи и Троицы
    if (counter == 1 && temp1 + 13 > 29)
    {
        celebrateDays[4][temp1 + 13 - 30] = 0;
        celebrateDays[5][temp3 - 1] = 0;
    }

    else if (counter == 1 && temp1 + 13 <= 29)
    {
        celebrateDays[3][temp1 + 13] = 0;
        celebrateDays[tempMonth][temp3 - 1] = 0;
    }
}
