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
void pasha_p (int year, int flag);

char *name[] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
int  *days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int isDayCelebrate; // Праздничный ли день

                               //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
int *celebrateDays[12][31] = {  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Январь
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Февраль
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
    int  i, y, month, year, horizontal, vertical, flag;
    char str[1024];

    system ("mode 70, 50");

    for (;;)
    {
        flag = 0;  // Флаг начала цикла

        printf (rus ("Введите год: "));
        year = gets(str);
        year = atoi(str);
        if (year < 1582 || year > 9999)
        {
            printf(rus ("Введите год от 1583 до 9999\n"));
            system("pause");
            system ("cls");
            continue;
        }
        horizontal = 1;
        vertical   = 2;
        month      = 1;

        pasha_p (year, flag);

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

        gotoxy (1, 38);

        printf(rus("*  1 января  - Новый год\n"));
        printf(rus(" *  7 января  - Рождество Христово\n"));
        if (year >= 1975)
            printf(rus(" *  8 марта   - Международный женский день\n"));
        if (year >= 1890)
            printf(rus(" *  1 мая     - День трудящихся\n"));
        if (year > 1944)
            printf(rus(" *  9 мая     - День Победы\n"));
        if (year > 1990)
        {
            printf(rus(" * 28 июня    - День Конституции Украины\n"));
            printf(rus(" * 24 августа - День независимости Украины\n"));
            printf(rus(" * 14 октября - День защитника Украины\n"));
        }

        flag = 1;            // Флаг конца цикла
        pasha_p(year, flag); // Передаем функции флаг конца цикла и сбрасываем дату Пасхи и Троицы

        gotoxy (1, 48);
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

    // Печатаем "шапку" над каждым месяцем
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

        // Если день праздничный, то выделяем его красным иначе белым
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

void pasha_p (int year, int flag)
{
    int a, b, c, d, e, temp1, temp2, temp3, tempMonth;

    // Определяем дату Пасхи
    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = (19 * a + 15) % 30;
    e = (2 * b + 4 * c + 6 * d + 6) % 7;

    temp1 = (d + e - 9) - 1;

/* ---- Записываем даты Пасхи и Троицы в массив ---- */
    // Если Пасха в маю
    if (temp1 + 13 > 29)
    {
        if (flag == 0 && celebrateDays[4][temp1 + 13 - 30] == 1)
            isDayCelebrate = 1;
        else if (flag == 0 && celebrateDays[4][temp1 + 13 - 30] == 0)
        {
            isDayCelebrate = 0;
            celebrateDays[4][temp1 + 13 - 30] = 1;
        }
        temp3 = temp1 + 13 - 30 + 50;
        temp2 = days_month[4];
        temp3 = temp3 - temp2;
        celebrateDays[5][temp3 - 1] = 1;
    }
    // Если Пасха в апреле
    else
    {
        if (flag == 0 && celebrateDays[3][temp1 + 13] == 1)
            isDayCelebrate = 1;
        else if (flag == 0 && celebrateDays[3][temp1 + 13] == 0)
        {
            isDayCelebrate = 0;
            celebrateDays[3][temp1 + 13] = 1;
        }
        temp3 = temp1 + 13 + 50;
        temp2 = days_month[3];
        temp3 = temp3 - temp2;
        if (temp3 > 31) // Если дней больше 31 то переходим на следующий месяц
        {
            tempMonth = 5;
            temp3 = temp3 - 31;
            celebrateDays[tempMonth][temp3 - 1] = 1;
        }
        else
        {
            tempMonth = 4;
            celebrateDays[tempMonth][temp3 - 1] = 1;
        }
    }

    // Сбрасываем даты Пасхи и Троицы
    if (flag == 1 && temp1 + 13 > 29) // Май
    {
        gotoxy(45, 38);
        printf(rus(" * %d мая   - Пасха\n"), temp1 + 13 - 30 + 1);
        gotoxy(45, 39);
        printf(rus(" * %d июня - Троица"), temp3);

        if (isDayCelebrate == 1);
        else
            celebrateDays[4][temp1 + 13 - 30] = 0;

        celebrateDays[5][temp3 - 1] = 0;
    }

    else if (flag == 1 && temp1 + 13 <= 29) // Апрель
    {
        gotoxy(45, 38);
        printf(rus("* %d апреля - Пасха\n"), temp1 + 13 + 1);
        gotoxy(45, 39);

        // Печатаем дату Троицы с разными количествами пробелов для выравнивания
        if (temp3 > 9)
        {
            if (tempMonth == 4)
            {
                if (temp1 + 13 + 1 < 10)
                    printf(rus("* %d мая   - Троица"), temp3);
                else
                    printf(rus("* %d мая    - Троица"), temp3);
            }
            if (tempMonth == 5)
                printf(rus("* %d июня   - Троица"), temp3);
        }
        else
            printf(rus("* %d июня    - Троица"), temp3);

        if (isDayCelebrate == 1);
        else
            celebrateDays[3][temp1 + 13] = 0;

        celebrateDays[tempMonth][temp3 - 1] = 0;
    }
}
