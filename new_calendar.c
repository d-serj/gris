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
    int day, month, year;

    for (;;)
    {
        printf (rus ("Введите год: "));
        scanf ("%d", &year);
        if (year == 0)
            break;
        printf (rus ("Введите месяц: "));
        scanf ("%d", &month);
        printf (rus ("Введите день: "));
        scanf ("%d", &day);
        printf (rus (name[calendar_func(day, month, year)]));
        printf ("\n");
    }
    return 0;
}
