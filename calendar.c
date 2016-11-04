#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char *rus (char *p)
{
    static char txt[1024];

    CharToOemA (p, txt);
    return txt;
}

void print_calendar ();

int main()
{
    int i, j;
    int month[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};

    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
          printf ("%2d", month[i][j]);
        }
        printf("\n");
    }

    printf (rus (" Пн Вт Ср Чт Пт Сб Вс\n\n"));

    print_calendar();

/*    for (;;)
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
    return 0;
}

// Выводим на экран месяц с 31 числом
void print_calendar()
{
    int j = 0;
    int i = 1;
    int stroke;
    int calendar[31];

    for (i = 0; i < 31; ++i)
    {
        calendar[i] = i + 1;
    }
    i = 0;

    while (i < 7)
    {
        printf ("%3d", calendar[i]);
        ++i;
    }
    printf ("\n");
    while (i >= 7 && i <= 13)
    {
        printf ("%3d", calendar[i]);
        ++i;
    }
    printf ("\n");
    while (i >= 13 && i <= 20)
    {
        printf ("%3d", calendar[i]);
        ++i;
    }
    printf ("\n");
    while (i >= 20 && i <= 27)
    {
        printf ("%3d", calendar[i]);
        ++i;
    }
    printf ("\n");

    while (i >= 27 && i <= 30)
    {
        printf ("%3d", calendar[i]);
        ++i;
    }
    printf("\n");
}
