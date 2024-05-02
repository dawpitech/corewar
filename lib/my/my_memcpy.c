/*
** EPITECH PROJECT, 2024
** memcpy
** File description:
** title
*/

#include "include/my.h"

void my_memcpy(void *src, size_t size, void *dest)
{
    for (size_t i = 0; i < size; i++)
        ((char *)dest)[i] = ((char *)src)[i];
}
