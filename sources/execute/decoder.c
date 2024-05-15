/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** decoder header
*/

#include <malloc.h>

#include "corewar.h"

uint8_t *decode_cb(arena_t *arena, uint32_t address)
{
    uint8_t *params = malloc(sizeof(uint8_t) * 4);
    uint8_t cb = arena->ram[address % MEM_SIZE];

    params[0] = (cb & 0xC0) >> 6;
    params[1] = (cb & 0x30) >> 4;
    params[2] = (cb & 0xC) >> 2;
    params[3] = (cb & 0x3);
    return params;
}
