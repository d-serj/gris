#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void)
{
    int a, b, multip, randWord, counter, max, incorrectAnswer;
    char word1[] = "Very good!";
    char word2[] = "Nice!";
    char word3[] = "Awesome!";
    char word4[] = "Excellent!";

    srand(time(NULL));
    counter = 0;
    incorrectAnswer = 0;
    max = 10;

    while (counter != max)
    {
        a = 1 + rand() % 9;
        b = 1 + rand() % 9;
        printf("How much is %d * %d ?\n", a, b);

        // Пока введенное пользователем число не будет равно правильному результату
        while (a * b != multip)
        {
            scanf("%d", &multip);
            randWord = rand() % 4;

            // Если правильный ответ рандомно выводим
            //1 из 4 поздравительных фраз
            if (multip == a * b)
            {
                switch (randWord)
                {
                    case 0:
                        printf("%s\n", word1);
                        break;
                    case 1:
                        printf("%s\n", word2);
                        break;
                    case 2:
                        printf("%s\n", word3);
                        break;
                    case 3:
                        printf("%s\n", word4);
                        break;
                }
                printf("\n");
            }
            else
            {
                printf("Wrong\n");
                printf("Try one more time\n");
                ++incorrectAnswer;
            }
        }
        // Обнуляем во избежание ошибки работы программы
        // при рандоме одинаковых по результату выражений
        multip = 0;
        ++counter;
    }
    printf("Your mistakes are %d", incorrectAnswer);

    return 0;
}
