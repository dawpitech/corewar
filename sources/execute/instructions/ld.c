/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <endian.h>
#include <malloc.h>

#include "corewar.h"
#include "op.h"

static int free_params(instruct_infos_t *params)
{
    free(params);
    return 0;
}

int execute_ld(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    uint32_t val;
    instruct_infos_t *params = decode_instruction(arena,
        &program->program_counter);

    if (params == NULL)
        return 1;
    val = params->params[0].value;
    if (params->params[0].size == T_IND) {
        val = read_uint32(arena, tmp + params->params[0].value % IDX_MOD);
        val = htobe32(val);
    }
    if ((params->params[1].value - 1) < 0 ||
        (params->params[1].value - 1) >= REG_NUMBER) {
        free(params);
        return 0;
    }
    program->registers[params->params[1].value - 1] = (int) val;
    program->carry_bit = val == 0;
    return free_params(params);
}
