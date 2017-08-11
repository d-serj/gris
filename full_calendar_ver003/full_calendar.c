#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

#define BACKGROUND 39
#define BACKGROUNDRED 36
#define RED 4
#define WHITE 7

typedef enum months
{JANUARY = 0, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

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
void pasha_p (int year, bool flag);
void clear_PashaWhitDay (int month1, int dayPasha, int month2, int dayWhitSunday);

char *name[] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
int  days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool isDayCelebrate;
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

/******************************************************************/
int main()
{
    int  i, y, month, year, horizontal, vertical;
    bool flag;
    char str[1024];

    // Размер окна
    system ("mode 70, 50");

    for (;;)
    {
        flag = false;  // Флаг начала цикла

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
        month      = FEBRUARY;

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

        flag = true;            // Флаг конца цикла
        pasha_p(year, flag);    // Передаем функции флаг конца цикла и сбрасываем дату Пасхи и Троицы

        gotoxy (1, 48);
        system ("pause");
        system ("cls");
    }

    return 0;
}


/*****************************************************************************/
void print_calendar (int month, int year, int horizontal, int vertical)
{
    int  i, y, firstDayOfMonth, tempDay, temp1, day;

    day = 1;

    // Определяем високосный год ((year%4 == 0 and year%100 != 0) or (year%400 == 0))
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        days_month[FEBRUARY] = 29;
    else
        days_month[FEBRUARY] = 28;

    if (month <= 2)
    {
        --year;
        day += 3;
    }

    // В какой день начинается месяц
    firstDayOfMonth = (day + year + year / 4 - year / 100 + year / 400 + (31 * month + 10) / 12) % 7;

    // Печатаем "шапку" над каждым месяцем
    gotoxy (horizontal, vertical);
    ++vertical;
    printf ("       ");
    printf (rus (name[month - 1]));
    gotoxy (horizontal, vertical);
    ++vertical;
    printf (rus (" Пн Вт Ср Чт Пт Сб Вс\n"));
    gotoxy (horizontal, vertical);

    // Печатаем количество пробелов в зависимости от дня начала месяца
    for (i = 1; i <= firstDayOfMonth; ++i)
        printf("   ");

    // Печатаем календарь на месяц
    for (i = 1; i <= days_month[month - 1]; ++i)
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

        //Переход на новую строку
        if ((i + firstDayOfMonth) % 7 == 0)
            gotoxy (horizontal, ++vertical);
    }

    setcolor(WHITE);
}


/*****************************************************************************/
void pasha_p (int year, bool flag)
{
    int a, b, c, d, e;
    int dayOfPasha, temp2;

    // День Святой Троицы (англ. Whit Sunday)
    int whitSundayDay;

    int tempMonth;

    // Определяем дату Пасхи
    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = (19 * a + 15) % 30;
    e = (2 * b + 4 * c + 6 * d + 6) % 7;

    dayOfPasha = (d + e - 9) - 1;

/* ---- Записываем даты Пасхи и Троицы в массив ---- */
    // Если Пасха в маю
    if (dayOfPasha + 13 > 29)
    {
        if (flag == 0 && celebrateDays[MAY][dayOfPasha + 13 - 30] == 1)
            isDayCelebrate = true;

        else if (flag == 0 && celebrateDays[MAY][dayOfPasha + 13 - 30] == 0)
        {
            isDayCelebrate = false;
            celebrateDays[MAY][dayOfPasha + 13 - 30] = 1;
        }

        // Определяем дату Троицы и зацисываем ее в массив
        whitSundayDay = dayOfPasha + 13 - 30 + 50 - days_month[MAY];
        celebrateDays[JUNE][whitSundayDay - 1] = 1;
    }

    // Если Пасха в апреле
    else
    {
        if (flag == false && celebrateDays[APRIL][dayOfPasha + 13] == 1)
            isDayCelebrate = true;
        else if (flag == false && celebrateDays[APRIL][dayOfPasha + 13] == 0)
        {
            isDayCelebrate = false;
            celebrateDays[APRIL][dayOfPasha + 13] = 1;
        }

        whitSundayDay = dayOfPasha + 13 + 50 - days_month[APRIL];

        if (whitSundayDay > 31)                                 // Если получили день троицы больше чем 31
        {
            tempMonth = JUNE;                                   // Сохраним значения месяца чтобы потом сбросить его в 0
            whitSundayDay = whitSundayDay - 31;
            celebrateDays[JUNE][whitSundayDay - 1] = 1;

            //if(flag == )
        }

        else
        {
            tempMonth = MAY;
            celebrateDays[MAY][whitSundayDay - 1] = 1;
        }

    }

    // Выводим даты празднования Пасхи и Троицы, затем сбрасываем даты в массиве
    if (flag == true && dayOfPasha + 13 > 29) // Май
    {
        gotoxy(45, 38);
        printf(rus(" * %d мая   - Пасха\n"), dayOfPasha + 13 - 30 + 1);
        gotoxy(45, 39);
        printf(rus(" * %d июня - Троица"), whitSundayDay);

        if (isDayCelebrate == false)
            celebrateDays[MAY][dayOfPasha + 13 - 30] = 0;

        celebrateDays[JUNE][whitSundayDay - 1] = 0;
    }


    else if (flag == true && dayOfPasha + 13 <= 29)                           // Апрель
    {
        gotoxy(45, 38);
        printf(rus("* %d апреля - Пасха\n"), dayOfPasha + 13 + 1);
        gotoxy(45, 39);

        if (tempMonth == MAY)
        {
            if (dayOfPasha + 13 + 1 < 10)
                printf(rus("* %2d мая   - Троица"), whitSundayDay);
            else
                printf(rus("* %2d мая    - Троица"), whitSundayDay);
        }

        if (tempMonth == JUNE)
            printf(rus("* %2d июня   - Троица"), whitSundayDay);

        else
            printf(rus("* %2d июня    - Троица"), whitSundayDay);


        if (!isDayCelebrate)
            celebrateDays[APRIL][dayOfPasha + 13] = 0;

    }

    celebrateDays[tempMonth][whitSundayDay - 1] = 0;
}

/*****************************************************************************/
void clear_PashaWhitDay (int monthOfPasha, int _dayOfPasha, int monthOfWhitSunday, int _whitSundayDay)
{
    if (monthOfPasha == MAY)
    {
        celebrateDays[MAY][_dayOfPasha + 13 - 30] = 0;
        celebrateDays[JUNE][_whitSundayDay - 1] = 0;
    }

    else
        celebrateDays[APRIL][_dayOfPasha + 13] = 0;

    celebrateDays[monthOfWhitSunday][_whitSundayDay - 1] = 0;
}
