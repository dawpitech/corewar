/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>
#include <stdint.h>
#include <stdlib.h>

#include "corewar.h"

static void update_owning(arena_t *arena, instruct_infos_t *infos,
    program_t *program, int32_t addr)
{
    for (int i = 0; i < 4; i++)
        arena->ram_owning[addr + i] = program->id;
    free(infos);
}

int execute_sti(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    instruct_infos_t *infos = decode_instruction(arena,
        &program->program_counter);
    uint32_t a;
    uint32_t b;
    uint32_t addr = 0;

    if (infos == NULL)
        return 1;
    a = infos->params[1].value;
    if (infos->params[1].size == T_REG)
        a = program->registers[infos->params[1].value - 1];
    b = infos->params[2].value;
    if (infos->params[2].size == T_REG)
        b = program->registers[infos->params[2].value - 1];
    addr = tmp + (a + b) % IDX_MOD;
    write_bytes(program->registers[infos->params[0].value - 1], REG_SIZE,
                tmp + (a + b) % IDX_MOD, arena);
    update_owning(arena, infos, program, addr);
    return 0;
}
