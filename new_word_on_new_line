#include <stdio.h>
#include <stdlib.h>

/* подсчет строк слов и символов*/
int main()
{
    int ch, n=0;

    //DOS: CTRL+z для EOF
    while((ch = getchar()) != EOF)
    {   //если считываемый символ "не символ-слово", то
        if(ch == ' ' || ch == '\t' || ch == '.' || ch == ',')
        {   //ставим '\n', и инкрементируем счетчик
            if(n == 0)
            {
                ++n;
                putchar('\n');
            }
        }
        else
        {   //обнуляем счетчик и печатаем "символ-слово"
            n = 0;
            putchar(ch);
        }
    }
    return 0;
}
