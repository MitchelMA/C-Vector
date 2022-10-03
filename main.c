#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector/vector.h"

void fillVec(Vector *vec, int amount);
void vector_print(Vector *vec);

int main(int argc, char *argv[])
{
    argv++;
    int num = atoi(*argv);
    num = num > 2 ? num : 4;

    // initialize a vector
    Vector *numvec = vector_create();
    // fill it with numbers
    fillVec(numvec, num);
    // change a value
    *(int *)vector_at(numvec, 2) = 20;

    // show data
    printf("count: %d\n", vector_getcount(numvec));
    printf("capacity: %d\n", vector_getcapacity(numvec));
    printf("items:\n");
    vector_print(numvec);

    // remove a value
    int *out;
    if (vector_remove(numvec, &out))
    {
        printf("\nremoved value: %d\n", *out);
        free(out);
        vector_print(numvec);
    }

    // flush the vector after removing all the values
    for (int i = 0; i < vector_getcount(numvec); i++)
    {
        int *outval;
        if (vector_remove(numvec, &outval))
        {
            free(outval);
        }
        else
        {
            printf("Failed to remove a value from the vector\n");
        }
    }

    // flushing the vector resets and frees all the heap allocated stuff
    vector_flush(numvec);
    printf("flushing the vector was successful: %s\n", vector_isflushed(numvec) == 1 ? "true" : "false");

    // now we can free the vector without creating a memory leak
    free(numvec);

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

void vector_print(Vector *vec)
{
    for (int i = 0; i < vector_getcount(vec); i++)
    {
        int *val = vector_at(vec, i);
        printf("element %2d: %p : %d\n", i, val, *val);
    }
}