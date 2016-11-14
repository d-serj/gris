#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char *rus (char *p)
{
    static char txt[1024];

    CharToOemA (p, txt);
    return txt;
}

int calendar_func (int d, int m, int y)
{
    int w;

    if (m <= 2)
    {
        --y;
        d += 3;
    }
    w = (d + y + y / 4 - y / 100 + y / 400 + (31 * m + 10) / 12) % 7;
    return w;
}

char *name[] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};

int main()
{
    int  i, y, w, day, month, year;
    char str[1024];
    int  days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (;;)
    {
        printf (rus ("Введите год: "));
        scanf ("%d", &year);

        if (year < 1582 || year > 9999)
        {
            printf("Error!\n");
            continue;
        }

        // ((year%4 == 0 and year%100 != 0) or (year%400 == 0))
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
            days_month[1] = 29;
        else
            days_month[1] = 28;

        printf (rus ("Введите месяц: "));
        scanf ("%d", &month);

        if (month < 1 || month > 12)
        {
            printf("Error!\n");
            continue;
        }

        printf (rus ("Введите день: "));
        scanf ("%d", &day);

        if (day < 1 || day > days_month[month - 1])
        {
            printf("Error!\n");
            continue;
        }

        y = calendar_func(day, month, year);
        printf (rus (name[y]));
        printf ("\n");

        printf (rus (" Пн Вт Ср Чт Пт Сб Вс\n"));

        // Сбрасываем день на 1е число и высчитываем в какой день начало месяца
        day = 1;
        y = calendar_func(day, month, year);

        // Печатаем количество пробелов в зависимости от дня начала месяца
        for (i = 1; i <= y; ++i)
            printf("   ");

        // Печатаем календарь на месяц
        w = days_month[month - 1];
        for (i = 1; i <= w; ++i)
        {
            printf ("%3d", i);
            if ((i + y) % 7 == 0)
                printf("\n");
        }

        printf("\n\n");
        system("pause");
        system("cls");
    }
    return 0;
}
