#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "radixsort.h"

void radixSort(int *list)
{
    int sorted[1000];

    int count[10] = {0};
    for (int place = 0; place < 5; place++)
    {
        for (int idx = 0; idx < 1000; idx++)
        {
            int digit = (list[idx] / (int)pow(10, place)) % 10;
            count[digit]++;
        }

        for (int dig = 1; dig < 10; dig++)
        {
            count[dig] += count[dig - 1];
        }

        for (int idx = 999; idx >= 0; idx--)
        {
            int digit = (list[idx] / (int)pow(10, place)) % 10;
            sorted[count[digit] - 1] = list[idx];
            count[digit]--;
        }

        for (int dig = 0; dig < 10; dig++)
        {
            count[dig] = 0;
        }

        memcpy(list, sorted, sizeof(int) * 1000);
    }
}
