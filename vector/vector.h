#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>

typedef struct _vector_impl Vector;

/**
 * @brief Allocates a new vector on the heap
 *
 * @return Vector*
 */
Vector *vector_create();

size_t vector_getcapacity(const Vector *vec);
size_t vector_getcount(const Vector *vec);
int vector_isflushed(const Vector *vec);

/**
 * @brief Append the value at the end of the vector
 *
 * @param vec The vector at which the value gets appended
 * @param value The value that gets appended
 * @return Succes
 */
int vector_append(Vector *vec, void *value);

int vector_insertbefore(Vector *vec, size_t idx, void *value);

/**
 * @brief Inserts value **after** the specified index `idx`.
 *
 * @param vec
 * @param idx
 * @param value
 * @return integer determining if inserting went succesful.
 */
int vector_insertafter(Vector *vec, size_t idx, void *value);

/**
 * @brief Removes the last element of the vector
 *
 * @param vec The vector from which the last element gets removed
 * @param out The memory address of the removed element
 * @return Succes
 */
int vector_remove(Vector *vec, void **out);

/**
 * @brief Gets the element at the specified index
 *
 * @param vec
 * @param idx
 * @return void*
 */
void *vector_at(const Vector *vec, size_t idx);

/**
 * @brief Frees the void-pointer array containing the memory addresses of values put into the vector.
 * It is recommended to free all the heap-allocated items in the vector before flushing.
 *
 * @param vec
 * @return int
 */
int vector_flush(Vector *vec);

/**
 * @brief Resets all the attributes of the vector, making it ready **after** it was flushed.
 * It checks if the vector was flushed or not, because of this an assertion will fail if it was not flushed.
 *
 * @param vec The vector that gets reset.
 * @return Succes of resetting
 */
int vector_reset(Vector *vec);

void print_adresses(Vector *vec);

#endif // __VECTOR_H__