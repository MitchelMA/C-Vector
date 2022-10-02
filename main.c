#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector/vector.h"

void fillVec(Vector *vec, int amount);

int main(int argc, char *argv[])
{
    argv++;
    int num = atoi(*argv);
    Vector *myvec = vector_create(sizeof(int));
    fillVec(myvec, num);
    int *terug = vector_at(myvec, 0);

    printf("size: %d\n", vector_getsize(myvec));
    printf("capacity: %d\n", vector_getcapacity(myvec));
    printf("address of first: %p: %d\n", terug, *terug);
    printf("values: \n");
    for (int i = 0; i < vector_getsize(myvec); i++)
    {
        void *val = vector_at(myvec, i);
        printf("\t%p: %d\n", val, *(int *)val);
    }

    return EXIT_SUCCESS;
}

void fillVec(Vector *vec, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        int *num = malloc(sizeof(int));
        *num = i + 1;
        vector_append(vec, num);
    }
}