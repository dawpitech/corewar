/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** executor header
*/

#include "corewar.h"
#include "instruction_handlers.h"

static
int execute_inst(int inst_code, arena_t *arena, program_t *program)
{
    if (inst_code <= 0 || inst_code > INSTRUCTION_HANDLERS_SIZE) {
        program->program_counter++;
        return EXIT_FAILURE_TECH;
    }
    program->cycles_before_next_instruction = op_tab[inst_code - 1].nbr_cycles;
    for (int j = 0; j < INSTRUCTION_HANDLERS_SIZE; j++)
        if (inst_code == instruction_handlers[j].instruction_code)
            return instruction_handlers[j].handler(arena, program);
    program->program_counter++;
    return EXIT_FAILURE_TECH;
}

int execute_next_inst(arena_t *arena, program_t *program)
{
    uint8_t ins = arena->ram[program->program_counter % MEM_SIZE];

    return execute_inst(ins, arena, program);
}
