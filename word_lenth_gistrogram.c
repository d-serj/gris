#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

#define IN 1
#define OUT 0
/* Гистрограмма длинны слов */
int main()
{
    int c, i, nwhite, nchars, state;
    int ndigit[16];
    nwhite = nchars = 0;

    for (i = 0; i < 16; ++i)
    {
        ndigit[i] = 0;
    }
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t' || c == ',' || c == '.' || c == '!' || c == '?')
        {
            ++nwhite;
            for (i = 0; i < nchars; ++i)
            {
                printf ("*");
            }
            printf ("\n");
            nchars = 0;
        }
        else
        {
            ++nchars;
        }
    }
    return 0;
}
