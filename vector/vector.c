#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

#define VECTOR_START_CAPACITY 16
#define VECTOR_CAPACITY_INCREASE 16
#define VECTOR_EMPTY_VALUE 0xdead

typedef struct _vector_impl
{
    size_t capacity;
    size_t count;
    int flushed;
    void **values;
} Vector;

// local prototypes ------

void _increase_capacity(Vector *vec);
void _decrease_capacity(Vector *vec);
void _clear_empty(Vector *vec);

// end local prototypes --

Vector *vector_create()
{
    Vector *tmp = malloc(sizeof(Vector));
    if (tmp == NULL)
        return NULL;
    tmp->capacity = VECTOR_START_CAPACITY;
    tmp->count = 0;
    tmp->flushed = 0;

    tmp->values = malloc(tmp->capacity * sizeof(uintptr_t));
    if (tmp->values == NULL)
    {
        free(tmp);
        return NULL;
    }
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
        _increase_capacity(vec);
        assert(vec->values != NULL && "Failed to allocate more memory for the vector to increase in capacity");
    }

    vec->values[vec->count - 1] = value;

    return 1;
}

int vector_insertbefore(Vector *vec, size_t idx, void *value)
{
    if (vec == NULL || idx < 1 || idx > vec->count + 1 || value == NULL)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    void *last = vec->values[vec->count - 1];
    if (!vector_append(vec, last))
    {
        return 0;
    }

    for (size_t i = vec->count - 1; i > idx - 1; i--)
    {
        vec->values[i] = vec->values[i - 1];
    }

    vec->values[idx - 1] = value;

    return 1;
}

int vector_insertafter(Vector *vec, size_t idx, void *value)
{
    if (vec == NULL || idx >= vec->count || value == NULL)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    // append the last value again into the list
    void *last = vec->values[vec->count - 1];
    if (!vector_append(vec, last))
    {
        return 0;
    }

    // shove everything above the specified idx up one
    for (size_t i = vec->count - 1; i > idx; i--)
    {
        vec->values[i] = vec->values[i - 1];
    }

    // set the new value at idx
    vec->values[idx + 1] = value;
    return 1;
}

int vector_remove(Vector *vec, void **out)
{
    if (vec == NULL || vec->count <= 0)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    void *last = vec->values[vec->count - 1];
    if (last == NULL)
        return 0;

    if (out != NULL)
        *out = last;

    vec->values[vec->count - 1] = VECTOR_EMPTY_VALUE;
    vec->count--;

    size_t diff = vec->capacity - vec->count;
    if (diff >= VECTOR_CAPACITY_INCREASE && vec->count > 0)
    {
        _decrease_capacity(vec);
        assert(vec->values != NULL && "Failed to decrease capacity of vector");
    }

    return 1;
}

int vector_removeat(Vector *vec, size_t idx, void **out)
{
    if (vec == NULL || idx >= vec->count)
        return 0;

    assert(!vec->flushed && "Tried to access vector after it was flushed");

    // get the selected element
    void *selected = vec->values[idx];
    if (selected == NULL)
        return 0;

    if (out != NULL)
        *out = selected;

    // set the selected index to empty
    vec->values[idx] = VECTOR_EMPTY_VALUE;
    // clear the empty slot
    _clear_empty(vec);

    // decrease in capacity when necessary
    size_t diff = vec->capacity - vec->count;
    if (diff >= VECTOR_CAPACITY_INCREASE && vec->count > 0)
    {
        _decrease_capacity(vec);
        assert(vec->values != NULL && "Failed to decrease capacity of vector");
    }

    return 1;
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

void vector_print_adresses(Vector *vec)
{
    for (size_t i = 0; i < vec->count; i++)
    {
        printf("%llu: %p\n", i, (vec->values + i));
    }
}

// local prototype implementations ------

void _increase_capacity(Vector *vec)
{
    vec->capacity += VECTOR_CAPACITY_INCREASE;
    vec->values = realloc(vec->values, vec->capacity * sizeof(uintptr_t));
}

void _decrease_capacity(Vector *vec)
{
    vec->capacity -= VECTOR_CAPACITY_INCREASE;
    vec->values = realloc(vec->values, vec->capacity * sizeof(uintptr_t));
}

void _clear_empty(Vector *vec)
{
    for (size_t idx = 0; idx < vec->count; idx++)
    {
        void *elem = vec->values[idx];
        if (elem == NULL || elem != VECTOR_EMPTY_VALUE)
            continue;

        for (size_t inner = idx; inner < vec->count; inner++)
        {
            vec->values[inner] = vec->values[inner + 1];
        }
        vec->count--;
    }
}

// end local prototype implementations --