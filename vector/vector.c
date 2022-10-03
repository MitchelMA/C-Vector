#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vector.h"

#define VECTOR_START_CAPACITY 16
#define VECTOR_CAPACITY_INCREASE 16
#define VECTOR_EMPTY_VALUE 0xdead

typedef struct _vector_impl
{
    void **values;
    size_t capacity;
    size_t count;
    int flushed;
} Vector;

// local prototypes ------

void increase_capacity(Vector *vec);

// end local prototypes --

Vector *vector_create()
{
    Vector *tmp = malloc(sizeof(Vector));
    tmp->values = malloc(VECTOR_START_CAPACITY * sizeof(uintptr_t));
    tmp->capacity = VECTOR_START_CAPACITY;
    tmp->count = 0;
    tmp->flushed = 0;
    return tmp;
}

size_t vector_getcapacity(const Vector *vec)
{
    if (vec == NULL)
        return 0;
    assert(!vec->flushed && "Tried to access vector after it was flushed");
    return vec->capacity;
}

size_t vector_getcount(const Vector *vec)
{
    if (vec == NULL)
        return 0;
    assert(!vec->flushed && "Tried to access vector after it was flushed");
    return vec->count;
}

int vector_isflushed(const Vector *vec)
{
    if (vec == NULL)
        return 0;
    return vec->flushed;
}

int vector_append(Vector *vec, void *value)
{
    if (vec == NULL || value == NULL)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    if (++vec->count > vec->capacity)
    {
        increase_capacity(vec);
        assert(vec->values != NULL && "Failed to allocate more memory for the vector to increase in capacity");
    }

    assert(vec->count < vec->capacity + 1 && "Element count got above capacity");
    vec->values[vec->count - 1] = value;

    return 1;
}

int vector_remove(Vector *vec, void **out)
{
    if (vec == NULL)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    if (out != NULL && vec->count > 0)
    {
        *out = vec->values[vec->count - 1];
        vec->values[vec->count - 1] = VECTOR_EMPTY_VALUE;
        vec->count--;
        return 1;
    }

    return 0;
}

void *vector_at(const Vector *vec, size_t idx)
{
    if (vec == NULL)
        return NULL;

    assert(!vec->flushed && "Tried to access vector after it was flushed");
    assert(idx < vec->count && "Index was out of bounds");
    return vec->values[idx];
}

int vector_flush(Vector *vec)
{
    if (vec == NULL)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    vec->flushed = 1;
    // reset all the values
    vec->capacity = 0;
    vec->count = 0;
    free(vec->values);
    return 1;
}

int vector_reset(Vector *vec)
{
    if (vec == NULL)
        return 0;

    assert(vec->flushed && "Tried to reset vector that was never flushed");

    vec->flushed = 0;
    vec->capacity = VECTOR_START_CAPACITY;
    vec->count = 0;
    vec->values = malloc(VECTOR_START_CAPACITY * sizeof(uintptr_t));
    return 1;
}

// local prototype implementations ------

void increase_capacity(Vector *vec)
{
    vec->capacity += VECTOR_CAPACITY_INCREASE;
    vec->values = realloc(vec->values, vec->capacity * sizeof(uintptr_t));
}

// end local prototype implementations --