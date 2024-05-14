/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** executor header
*/

#include <endian.h>
#include <stdlib.h>
#include <unistd.h>

#include "corewar.h"
#include "my.h"
#include "my_printf.h"

static
int execute_live(arena_t *arena, program_t *program)
{
    uint32_t prog_id;

    program->program_counter += 1;
    prog_id = read_uint32(arena, program->program_counter);
    prog_id = htobe32(prog_id);
    if (prog_id >= MAX_ARGS_NUMBER)
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
    instruct_infos_t *infos = decode_instruction(arena, &program->program_counter);

    if (infos == NULL)
        return 1;
    write_bytes(program->registers[infos->params[0].value - 1], 4,
                tmp + (infos->params[1].value + infos->params[2].value) % IDX_MOD, arena);
    free(infos);
    return 0;
}

static
int execute_aff(arena_t *arena, program_t *program)
{
    instruct_infos_t *infos = decode_instruction(arena, &program->program_counter);
    char chr;

    if (infos == NULL)
        return 1;
    if (infos->params[0].size != REG_SIZE || infos->params[0].value > REG_NUMBER)
        return 1;
    chr = (char) (program->registers[infos->params[0].value - 1] % 256);
    write(STDOUT_FILENO, &chr,1);
    return 0;
}

static
int find_opcode(uint8_t name)
{
    for (int i = 0; op_tab[i].mnemonique != 0; i++)
        if (name == op_tab[i].code)
            return i;
    return -1;
}

static
int execute_inst(int i, arena_t *arena, program_t *program)
{
    program->cycles_before_next_instruction = op_tab[i].nbr_cycles;
    if (my_strcmp(op_tab[i].mnemonique, "live") == 0)
        return execute_live(arena, program);
    if (my_strcmp(op_tab[i].mnemonique, "ld") == 0)
        return execute_ld(arena, program);
    if (my_strcmp(op_tab[i].mnemonique, "sti") == 0)
        return execute_sti(arena, program);
    if (my_strcmp(op_tab[i].mnemonique, "aff") == 0)
        return execute_aff(arena, program);
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
