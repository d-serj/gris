//#include "windows.h"
#include "stdafx.h"
char *rus (char *p)
{
	static char txt[1024];

	CharToOemA (p, txt);
	return txt;
}

int main(int argc, char* argv[])
{
    int cost, change;
    int cash = 100;
    int fifty = 50;
    int twentyf = 25;
    int ten = 10;
    int five = 5;
    int two = 2;
    int one = 1;
    
    printf (rus ("Автомат выдачи сдачи\n\n"));
    
    for (;;)
    {
        printf (rus ("Введите стоимость товара от 1 до 100 копеек: "));
        scanf ("%d", &cost);
        
        if (cost < 1 || cost > 99)
        {
            printf (rus ("Ошибка, от 1 до 99\n"));
            continue;
        }
        else
        {
            printf (rus ("Ваша  сдача: \n"));   
                
			change = cash - cost;

            while (change > 0)
            {
				if (change >= fifty)
				{
					change = change - fifty;
					printf ("50\n", fifty);
				}
                else if (change >= twentyf)
                {
					change = change - twentyf;
					printf ("25\n", twentyf);
                }
                else if (change >= ten)
                {
					change = change - ten;
					printf ("10\n", ten);
                }
                else if (change >= five)
                {
					change = change - five;
					printf ("5\n", five);
                }
                else if (change >= two)
                {
					change = change - two;
					printf ("2\n", two);   
                }
                else if (change >= one)
                {
					change = change - one;
					printf ("1\n", one);     
                }
            }
			printf ("\n");
        }        
    }    
	return 0;
}
