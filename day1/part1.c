#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void radixSort(int *list)
{
    int sorted[1000];

    int count[10] = {0};
    for(int place = 0; place < 5; place++)
    {
        for(int idx = 0; idx < 1000; idx++)
        {
            int digit = (list[idx] / (int) pow(10, place)) % 10;
            count[digit]++;
        }

        for(int dig = 1; dig < 10; dig++)
        {
            count[dig] += count[dig - 1];
        }

        for(int idx = 999; idx >= 0; idx--)
        {
            int digit = (list[idx] / (int) pow(10, place)) % 10;
            sorted[count[digit] - 1] = list[idx];
            count[digit]--;
        }

        for(int dig = 0; dig < 10; dig++)
        {
            count[dig] = 0;
        }

        memcpy(list, sorted, sizeof(int) * 1000);
    }
}

int main(){
    FILE *file = fopen("../inputs/day1.txt", "r");

    if(file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int left[1000];
    int right[1000];

    char buffer[6];
    buffer[5] = '\0';

    for(int i = 0; i < 1000; i++)
    {
        fread(buffer, sizeof(char), 5, file);
        left[i] = atoi(buffer); 
        fseek(file, 3, SEEK_CUR);
        fread(buffer, sizeof(char), 5, file);
        right[i] = atoi(buffer); 
        fseek(file, 1, SEEK_CUR);
    }

    radixSort(left);
    radixSort(right);

    int count = 0;
    for(int i = 0; i < 1000; i++)
    {
        count += abs(left[i] - right[i]);
    }

    printf("%d\n", count);
}