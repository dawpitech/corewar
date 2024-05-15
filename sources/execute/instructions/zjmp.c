/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <endian.h>

#include "corewar.h"

int execute_zjmp(arena_t *arena, program_t *program)
{
    int16_t addr = 0;

    addr = read_int16(arena, program->program_counter + 1);
    addr = htobe16(addr);
    if (program->carry_bit == 0)
        return 0;
    program->program_counter += addr;
    program->carry_bit = 0;
    return 0;
}
