/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** writer header
*/

#include "corewar.h"
#include "op.h"
#include <endian.h>
#include <stdint.h>

void write_bytes(long num, int byte_nb, uint32_t address, arena_t *arena)
{
    char extracted_byte = 0;

    if (byte_nb == 2)
        num = htobe16(num);
    if (byte_nb == 4)
        num = htobe32(num);
    if (byte_nb < 1)
        return;
    for (int i = 0; i < byte_nb; i++) {
        extracted_byte = (num >> (8 * i)) & 0xFF;
        arena->ram[address + i] = extracted_byte;
    }
}
