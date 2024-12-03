#include <stdio.h>
#include <stdlib.h>

#include "radixsort.h"
#include "file.h"

int main()
{
    struct input i = readInput();

    radixSort(i.left);
    radixSort(i.right);

    int similarity = 0;

    int r = 0;
    for(int l = 0; l < 1000; l++){
        int count = 0;
        for(; i.right[r] <= i.left[l] && r < 1000; r++){
            if(i.right[r] == i.left[l]){
                count++;
            }
        }
        similarity += count * i.left[l];
    }

    free(i.left);
    free(i.right);

    printf("%d\n", similarity);
}