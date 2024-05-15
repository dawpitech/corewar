/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>
#include <stddef.h>

#include "corewar.h"
#include "my.h"

void *my_realloc(void *ptr, size_t new_size, size_t old_size)
{
    void *new_ptr;

    if (ptr == NULL)
        return malloc(new_size);
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    my_memcpy(ptr, old_size, new_ptr);
    free(ptr);
    return new_ptr;
}
