/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>

#include "corewar.h"

int execute_st(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    uint32_t val = 0;
    instruct_infos_t *params = decode_instruction(arena,
            &program->program_counter);

    if (params == NULL)
        return 1;
    val = tmp + params->params[1].value % IDX_MOD;
    if (params->params[1].size == T_DIR)
        val = params->params[1].value;
    if (params->params[1].size == T_REG) {
        program->registers[params->params[1].value - 1] =
                program->registers[params->params[0].value - 1];
        free(params);
        return 0;
    }
    write_bytes(program->registers[params->params[0].value], 4, val, arena);
    free(params);
    return 0;
}
