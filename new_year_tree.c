#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input, i, j, y;
    char str[1024];

    while (1)
    {
        input = gets(str);
        input = atoi(str);

        if (input > 38 || input < 2)
        {
            printf ("Error, input number from 2 to 38\n");
            system("pause");
            system("cls");
            continue;
        }
        for (i = 0; i <= input; ++i)
            printf(" ");
        printf("*\n");

        for (i = 1; i <= input; ++i)
        {
            for (j = input - i; j >=0; --j)
                printf (" ");

            for (y = 1; y <= i; ++y)
                printf("/");

            printf("|");

            for (y = 1; y <= i; ++y)
                printf("\\");

            printf("\n");
        }
        for (i = 1; i <= input; ++i)
            printf(" ");

        printf("|||\n");
        system("pause");
        system("cls");
    }
    return 0;
}
