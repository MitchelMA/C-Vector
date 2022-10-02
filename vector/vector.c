#include <stdlib.h>
#include <assert.h>
#include "vector.h"

#define VECTOR_START_CAPACITY 8
#define VECTOR_CAPACITY_INCREASE 8
#define VECTOR_EMPTY_VALUE NULL

struct _vector_impl
{
    void **values;
    size_t capacity;
    size_t count;
    size_t elem_size;
};

Vector *vector_create(size_t elem_size)
{
    struct _vector_impl *tmp = malloc(sizeof(struct _vector_impl));
    tmp->values = calloc(VECTOR_START_CAPACITY, elem_size);
    tmp->capacity = VECTOR_START_CAPACITY;
    tmp->count = 0;
    tmp->elem_size = elem_size;
    return tmp;
}

size_t vector_getcapacity(Vector *vec)
{
    return ((struct _vector_impl *)vec)->capacity;
}

size_t vector_getsize(Vector *vec)
{
    return ((struct _vector_impl *)vec)->count;
}

void vector_append(Vector *vec, void *value)
{
    struct _vector_impl *impl = (struct _vector_impl *)vec;
    assert(impl->count <= impl->capacity);
    if (++impl->count >= impl->capacity)
    {
        impl->capacity += VECTOR_CAPACITY_INCREASE;
        impl->values = realloc(impl->values, impl->capacity * impl->elem_size);
    }
    impl->values[impl->count - 1] = value;
}

void *vector_at(const Vector *vec, size_t idx)
{
    struct _vector_impl *impl = (struct _vector_impl *)vec;
    assert(idx < impl->count);
    return impl->values[idx];
}