/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** executor header
*/

#include "corewar.h"
#include "op.h"
#include "my.h"
#include "my_printf.h"
#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static
int execute_live(arena_t *arena, program_t *program)
{
    uint32_t prog_id;

    program->program_counter += 1;
    prog_id = read_uint32(arena, program->program_counter);
    prog_id = htobe32(prog_id);
    if (prog_id > MAX_ARGS_NUMBER)
        return EXIT_FAILURE_TECH;
    program->program_counter += 4;
    arena->programs[prog_id].cycles_before_die = CYCLE_TO_DIE;
    my_printf("The player %d(%s) is alive.\n", prog_id,
        arena->programs[prog_id].name);
    return EXIT_SUCCESS_TECH;
}

static
int execute_ld(arena_t *arena, program_t *program)
{
    return 0;
}

static
int execute_sti(arena_t *arena, program_t *program)
{
    uint32_t tmp = program->program_counter;
    instruct_params_t *params = decode_instruction(arena,
        &program->program_counter);

    if (params == NULL)
        return 1;
    write_bytes(program->registers[params->p1_value - 1], 4,
                tmp + (params->p2_value + params->p3_value) % IDX_MOD, arena);
    free(params);
    return 0;
}

int find_opcode(uint8_t name)
{
    for (int i = 0; op_tab[i].mnemonique != 0; i++)
        if (name == op_tab[i].code)
            return i;
    return -1;
}

int execute_inst(int i, arena_t *arena, program_t *program)
{
    program->cycles_before_next_instruction = op_tab[i].nbr_cycles;
    if (my_strcmp(op_tab[i].mnemonique, "live") == 0)
        return execute_live(arena, program);
    if (my_strcmp(op_tab[i].mnemonique, "ld") == 0)
        return execute_ld(arena, program);
    if (my_strcmp(op_tab[i].mnemonique, "sti") == 0)
        return execute_sti(arena, program);
    return EXIT_FAILURE_TECH;
}

int execute_next_inst(arena_t *arena, program_t *program)
{
    uint8_t ins = arena->ram[program->program_counter];
    int i = find_opcode(ins);

    if (i == -1)
        return EXIT_FAILURE_TECH;
    return execute_inst(i, arena, program);
}
