/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>

#include "corewar.h"

int32_t read_int32(arena_t *arena, uint32_t tmp)
{
    int32_t s;

    if (IND_SIZE == 1)
        s = read_uint8(arena, tmp + 3 % IDX_MOD) + 4;
    if (IND_SIZE == 2)
        s = read_uint16(arena, tmp + 3 % IDX_MOD) + 4;
    if (IND_SIZE == 4)
        s = read_uint32(arena, tmp + 3 % IDX_MOD) + 4;
    if (REG_SIZE == 1)
        s = read_uint8(arena, tmp + s % IDX_MOD);
    if (REG_SIZE == 2)
        s = read_uint16(arena, tmp + s % IDX_MOD);
    if (REG_SIZE == 4)
        s = read_uint32(arena, tmp + s % IDX_MOD);
    return s;
}

int execute_ldi(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    instruct_infos_t *infos = decode_instruction(arena,
        &program->program_counter);
    int32_t a;
    int32_t b;
    int32_t s;

    if (infos == NULL || infos->params[2].size != T_REG)
        return 1;
    a = infos->params[0].value;
    if (infos->params[0].size == T_REG)
        a = program->registers[a];
    b = infos->params[1].value;
    if (infos->params[1].size == T_REG)
        b = program->registers[b];
    s = read_int32(arena, tmp);
    program->registers[infos->params[2].value] = s;
    program->carry_bit = 1;
    return 0;
}