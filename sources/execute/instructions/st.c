/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>
#include <endian.h>

#include "corewar.h"

int execute_st(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    uint32_t val;
    instruct_infos_t *params = decode_instruction(arena,
            &program->program_counter);

    if (params == NULL)
        return 1;
    val = read_uint32(arena, tmp + params->params[1].value % IDX_MOD);
    val = htobe32(val);
    if (params->params[1].size == T_IND)
        val = params->params[1].value;
    if (params->params[1].size == T_REG) {
        program->registers[params->params[1].value - 1] =
                program->registers[params->params[0].value - 1];
        free(params);
        return 0;
    }
    write_bytes(program->registers[params->params[0].value], 4, val, arena);
    if (params->params[1].size == T_DIR)
	for (int i = 0; i < 4; i++)
	    arena->ram_owning[val + i] = program->id;
    free(params);
    return 0;
}
