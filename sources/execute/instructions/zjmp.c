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
    uint32_t tmp = program->program_counter;
    int16_t addr;

    addr = read_int16(arena, program->program_counter + 1);
    addr = htobe16(addr);
    program->program_counter += 2;
    if (program->carry_bit == 0)
        return 0;
    program->program_counter = tmp + addr % IDX_MOD;
    program->carry_bit = 0;
    return 0;
}
