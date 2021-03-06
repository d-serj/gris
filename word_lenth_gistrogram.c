#include <stdio.h>
#include <stdlib.h>

/* Гистрограмма длинны слов */
int main()
{
    int i, j, c, nc;
    int nwords[16] = {0};

    i = j = c = nc = 0;

    // Ctrl + z для EOF
    while ((c = getchar()) != EOF)
    {
        // Накапливаем символы слова
        ++nc;

        // Если слово закончилось записываем накопленное в соответствующую длине слова ячейку массива
        // и обнуляем счетчик
        if (c == ' ' || c == '\n' || c == '\t' || c == '.' || c == ',' || c == '!' || c == '?')
        {
            ++nwords[nc - 1];
            nc = 0;
        }
    }

    // Выводим гистрограмму длины слов
    for (i = 0; i < 16; ++i)
    {
        printf (i < 10 ? " %d " : "%d ", i);

        // Печатаем одну * за каждое слово определенной длинны
        for (j = nwords[i]; j > 0; --j)
        {
            printf ("*");
        }
        printf ("\a\n");
    }
    return 0;
}
