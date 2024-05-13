/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** reader header
*/

#include "corewar.h"

/**
 * Read a 32 bits value from the arena
 * @param arena the arena type
 * @param address the address to read from
 * @return uint32 value read
 */
uint32_t read_uint32(arena_t *arena, uint32_t address)
{
    return (arena->ram[address] | (arena->ram[address + 1] << 8) |
        (arena->ram[address + 2] << 16) | (arena->ram[address + 3] << 24));
}

uint8_t read_uint8(arena_t *arena, uint32_t address)
{
    return (arena->ram[address]);
}

uint16_t read_uint16(arena_t *arena, uint32_t address)
{
    return (arena->ram[address] | (arena->ram[address + 1] << 8));
}
