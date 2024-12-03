#include <stdio.h>
#include <stdlib.h>

#include "file.h"

struct input readInput()
{
    FILE *file = fopen("../inputs/day1.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file\n");
    }

    int *left = (int *)malloc(1000 * sizeof(int));
    int *right = (int *)malloc(1000 * sizeof(int));

    char buffer[6];
    buffer[5] = '\0';

    for (int i = 0; i < 1000; i++)
    {
        fread(buffer, sizeof(char), 5, file);
        left[i] = atoi(buffer);
        fseek(file, 3, SEEK_CUR);
        fread(buffer, sizeof(char), 5, file);
        right[i] = atoi(buffer);
        fseek(file, 1, SEEK_CUR);
    }

    struct input i;
    i.left = left;
    i.right = right;
    return i;
    
}