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
    uint8_t cb = arena->ram[address];

    params[0] = (cb & 0b11000000) >> 6;
    params[1] = (cb & 0b00110000) >> 4;
    params[2] = (cb & 0b00001100) >> 2;
    params[3] = (cb & 0b00000011);
    return params;
}
