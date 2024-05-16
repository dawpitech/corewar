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

int execute_ld(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    uint32_t val;
    instruct_infos_t *params = decode_instruction(arena,
        &program->program_counter);

    if (params == NULL)
        return 1;
    if (params->params[0].size == T_IND) {
        val = read_uint32(arena, tmp + params->params[0].value % IDX_MOD);
        val = htobe32(val);
    } else {
        val = params->params[0].value;
    }
    if ((params->params[1].value - 1) < 0 ||
        (params->params[1].value - 1) > REG_NUMBER)
        return 0;
    program->registers[params->params[1].value - 1] = (int) val;
    if (val == 0)
        program->carry_bit = 1;
    else
        program->carry_bit = 0;
    free(params);
    return 0;
}
