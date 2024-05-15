/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <malloc.h>
#include <unistd.h>

#include "corewar.h"

int execute_aff(arena_t *arena, program_t *program)
{
    instruct_infos_t *infos = decode_instruction(arena,
        &program->program_counter);
    char chr;

    if (infos == NULL)
        return 1;
    if (infos->params[0].size != T_REG ||
        infos->params[0].value > REG_NUMBER)
        return 1;
    chr = (char) (program->registers[infos->params[0].value - 1] % 256);
    write(STDOUT_FILENO, &chr, 1);
    free(infos);
    return 0;
}
