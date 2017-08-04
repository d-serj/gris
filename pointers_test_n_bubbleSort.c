#include <stdlib.h>
#include <stdio.h>

#define SIZE 9

void swap(int*, int*);
void array_print(int*, int);
void array_sort(int*, int);

int main ()
{
    int arr[SIZE] = {4, 2, 5, 3, 1, 151, 5, 46, 33};
    int a = 1, b = 2;

    array_sort(arr, SIZE);
    array_print(arr, SIZE);

    swap(&a, &b);
    printf("%d, %d", a, b);

    return 0;
}

void array_print(int *incomArrToPrint, int arrSize)
{
    int i;

    for (i = 0; i < arrSize; ++i)
        printf ("%d ", *incomArrToPrint++);

    putchar('\n');
}

void array_sort(int *arrToSort, int arrSize)
{
    int i, j;

    for(i = 0; i < arrSize; ++i)
        for(j = 0; j < arrSize - i - 1; ++j)
        {
            if (arrToSort[j] > arrToSort[j + 1])
                swap(&arrToSort[j], &arrToSort[j + 1]);
        }
}

void swap (int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
