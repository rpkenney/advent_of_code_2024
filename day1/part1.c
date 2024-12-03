#include <stdio.h>
#include <stdlib.h>

#include "radixsort.h"
#include "file.h"

int main()
{
    struct input i = readInput();

    radixSort(i.left);
    radixSort(i.right);

    int count = 0;
    for (int idx = 0; idx < 1000; idx++)
    {
        count += abs(i.left[idx] - i.right[idx]);
    }

    free(i.left);
    free(i.right);

    printf("%d\n", count);
}