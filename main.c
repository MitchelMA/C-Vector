#include <stdio.h>
#include <stdlib.h>
#include "vector/vector.h"

int main()
{
    Vector *myvec = vector_create(sizeof(int));
    int mooi_getal = 8;
    vector_append(myvec, &mooi_getal);
    int *terug = vector_at(myvec, 0);

    printf("size: %d\n", vector_getsize(myvec));
    printf("capacity: %d\n", vector_getcapacity(myvec));
    printf("value was: %d\n", *terug);

    return EXIT_SUCCESS;
}