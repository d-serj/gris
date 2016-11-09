#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char *rus (char *p)
{
    static char txt[1024];

    CharToOemA (p, txt);
    return txt;
}

int calendar_func (int day, int month, int year);

int main()
{
    int i, n, day, month, year;

    day = 1;

    for (;;)
    {
        printf (rus ("Введите год: "));
        scanf ("%d", &year);
        printf (rus ("Введите месяц: "));
        scanf ("%d", &month);
        printf (rus (" Пн Вт Ср Чт Пт Сб Вс\n\n"));

        n = calendar_func(day, month, year);
        for (i = 0; i < n + 1; ++i)
        {
            printf ("   ");
        }

        for (i = 1; i <= 31; ++i)
        {
            printf ("  %d", i);
            if ((i + n) % 7 == 0)
            {
                printf ("\n");
            }
        }

        printf ("\n");


        /*  for (;;)
            {
                scanf("%d", &i);
                if (!(i % 4))
                {
                    printf ("Delitsya\n");
                }
                else
                {
                    printf ("Ne delitsya\n");
                }
            }
        */
    }
    return 0;
}

// Функция определения в какой день начинается месяц
int calendar_func (int d, int m, int y)
{
    if (m <= 2)
    {
        --y;
        d += 3;
    }
    return (d + y + y / 4 + y / 400 + (31 * m + 10) / 12) % 7;
}
