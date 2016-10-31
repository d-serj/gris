#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char *rus (char *p)
{
    static char txt[1024];

    CharToOemA (p, txt);
    return txt;
}

void pasha_p (int year);
void pasha_k (int year);

int main()
{
    int year;
    char str[1024];

    printf (rus ("Программа определения даты Пасхи v1.0\n\n"));
    printf (rus ("Пожалуйста, вводите год c 1582 по 9999\n\n"));

    for (;;)
    {
        printf (rus ("Пожалуйста, введите год: "));
        gets (str);
        year = atoi (str);

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
void pasha_p (int year)
{
    int a, b, c, d, e, tmp;

    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = (19 * a + 15) % 30;
    e = (2 * b + 4 * c + 6 * d + 6) % 7;

    tmp = d + e - 9;
    if (tmp + 13 > 30)
    {
        printf (rus ("Православная Пасха %d мая\n"), tmp + 13 - 30);
    }
    else
    {
        printf (rus ("Православная Пасха %d апреля\n"), tmp + 13);
    }
}

// Католическая пасха
void pasha_k (int year)
{
    int a, b, c, d, e, m, n, k, p, q, tmp;

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
    tmp = 22 + d + e;

    // Если d = 29 и e = 6, то вместо 26 апреля будет 19 апреля
    if (d == 29 && e == 6)
    {
        printf (rus ("Католическая Пасха 19 апреля\n\n"));
    }

    // Если d = 28, e = 6 и (11M + 11) mod 30 < 19, то вместо 25 апреля будет 18 апреля
    else if (d == 28 && e == 6 && ((11 * m + 11) % 30) < 19)
    {
        printf (rus ("Католическая Пасха 18 апреля\n\n"));
    }
    else if (tmp > 0 && tmp < 32)
    {
        printf (rus ("Католическая Пасха %d марта\n\n"), tmp);
    }
    else
    {
        printf (rus ("Католическая Пасха %d апреля\n\n"), d + e - 9);
    }
}
