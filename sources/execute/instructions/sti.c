/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>

#include "corewar.h"

int execute_sti(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    instruct_infos_t *infos = decode_instruction(arena,
        &program->program_counter);
    uint32_t a;
    uint32_t b;

    if (infos == NULL)
        return 1;
    a = infos->params[1].value;
    if (infos->params[1].size == T_REG)
	a = program->registers[infos->params[1].value - 1];
    b = infos->params[2].value;
    if (infos->params[2].size == T_REG)
	b = program->registers[infos->params[2].value - 1];
    write_bytes(program->registers[infos->params[0].value - 1], 4,
                tmp + (a +
                b) % IDX_MOD, arena);
    for (int i = 0; i < 4; i++)
        arena->ram_owning[(tmp + (a + b) % IDX_MOD) + i] = program->id;
    free(infos);
    return 0;
}
