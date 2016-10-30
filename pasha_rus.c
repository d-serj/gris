#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char *rus (char *p)
{
    static char txt[1024];

    CharToOemA (p, txt);
    return txt;
}

int pasha_p (int year);
int pasha_k (int year);

int main()
{
    int year, c;

    printf (rus ("Программа определения даты Пасхи v1.0\n\n"));
    printf (rus ("Пожалуйста, вводите год c 1582 по 9999\n\n"));

    for (;;) // Бесконечный цикл
    {

        printf (rus ("Пожалуйста, введите год: "));
        scanf ("%d", &year);

        if (year < 1582 || year > 9999)
        {
            printf (rus ("Ошибка!\n"));
            continue;
        }

        pasha_p (year);
        pasha_k (year);
    }
    return 0;
}
// Православная Пасха
int pasha_p (int year)
{
    int p, a, b, c, d, e;

    a = b = c = d = e = 0;

    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = (19 * a + 15) % 30;
    e = (2 * b + 4 * c + 6 * d + 6) % 7;

    if (((d + e - 9) + 13) > 30)
    {
        return printf (rus ("Православная Пасха %d мая\n"), p = ((d + e - 9) + 13) - 30);
    }
    else
    {
        return printf (rus ("Православная Пасха %d апреля\n"), p = (d + e - 9) + 13);
    }
}
// Католическая пасха
int pasha_k (int year)
{
    int a, b, c, d, e, m, n, k, p, q;

    a = b = c = d = e = k = p = q = m = n = 0;

    a = year % 19;
    b = year % 4;
    c = year % 7;
    k = year / 100;
    p = (13 + 8 * k) / 25;
    q = k / 4;
    m = (15 - p + k - q) % 30;
    n = (4 + k - q) % 7;
    d = (19 * a + m) % 30;
    e = (2 * b + 4 * c + 6 * d + n) % 7;

    if (d == 29 && e == 6)
    {
        return printf (rus ("Католическая Пасха 19 апреля\n\n"));
    }

    else if (d == 28 && e == 6 && ((11 * m + 11) % 30) < 19)
    {
        return printf (rus ("Католическая Пасха 18 апреля\n\n"));
    }

    else if ((22 + d + e) > 0 && (22 + d + e) < 32)
    {
        return printf (rus ("Католическая Пасха %d марта\n\n"), 22 + d + e);
    }
    else
    {
        return printf (rus ("Католическая Пасха %d апреля\n\n"), d + e - 9);
    }
}
