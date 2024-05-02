/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include "corewar.h"
#include "arguments.h"
#include "my.h"

int corewar(int argc, char const **argv)
{
    arena_t arena;

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return print_help();
    my_memset(&arena, 0, sizeof(arena_t));
    arena.cycle_to_dump = -1;
    if (parse_arguments(argc, argv, &arena))
        return EXIT_FAILURE_TECH;
    return EXIT_SUCCESS_TECH;
}
