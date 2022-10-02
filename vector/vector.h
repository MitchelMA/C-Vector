#include <stdint.h>

typedef struct _vector_impl Vector;

Vector *vector_create(size_t elem_size);
size_t vector_getcapacity(Vector *vec);
size_t vector_getsize(Vector *vec);
void vector_append(Vector *vec, void *value);
void *vector_at(const Vector *vec, size_t idx);
