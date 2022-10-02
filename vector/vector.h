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
size_t vector_getsize(const Vector *vec);

/**
 * @brief Append the value at the end of the vector
 *
 * @param vec The vector at which the value gets appended
 * @param value The value that gets appended
 * @return Succes
 */
int vector_append(Vector *vec, void *value);

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
void vector_flush(Vector *vec);

#endif // __VECTOR_H__