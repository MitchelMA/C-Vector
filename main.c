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
    printf("count: %llu\n", vector_getcount(numvec));
    printf("capacity: %llu\n", vector_getcapacity(numvec));
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

    int *insertedval = malloc(sizeof(int));
    *insertedval = 99;
    size_t oldcount = vector_getcount(numvec);
    int insertidx = 9;
    if (vector_insertafter(numvec, insertidx, insertedval))
    {
        printf("count before insert: %llu\n", oldcount);
        printf("successfully inserted value of %d into the vector at %d\n", *insertedval, insertidx + 1);
        printf("count after insert: %d\n", vector_getcount(numvec));
        vector_print(numvec);
    }

    // flush the vector after removing all the values
    size_t count = vector_getcount(numvec);
    printf("vector count before remove: %llu\n", count);
    for (size_t i = 0; i < count; i++)
    {
        void *outval;
        if (vector_remove(numvec, &outval))
        {
            free(outval);
        }
        else
        {
            printf("Failed to remove a value from the vector\n");
        }
    }
    printf("vector count after remove: %llu\n", vector_getcount(numvec));
    printf("vector capacity at the end: %llu\n", vector_getcapacity(numvec));

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
    for (size_t i = 0; i < vector_getcount(vec); i++)
    {
        int *val = vector_at(vec, i);
        printf("element %2llu: %p : %d\n", i, val, *val);
    }
}