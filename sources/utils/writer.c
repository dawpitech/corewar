/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** writer header
*/

#include <endian.h>

#include "corewar.h"

void write_bytes(long num, int byte_nb, uint32_t address, arena_t *arena)
{
    char extracted_byte;

    if (byte_nb == 2)
        num = htobe16(num);
    if (byte_nb == 4)
        num = htobe32(num);
    if (byte_nb < 1)
        return;
    for (int i = 0; i < byte_nb; i++) {
        extracted_byte = (char) ((num >> (8 * i)) & 0xFF);
        arena->ram[(address + i) % MEM_SIZE] = extracted_byte;
    }
}
