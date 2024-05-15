/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include "corewar.h"
#include "arguments.h"
#include "my.h"
#include "arena.h"
#include "my_printf.h"
#include "op.h"
#include <stdint.h>
#include "visuals.h"

static int dump_cycle(arena_t *arena)
{
    for (uint32_t i = 0; i < MEM_SIZE; i++) {
        if (i != 0 && i % 32 == 0)
            my_putchar('\n');
        if (arena->ram[i] <= 0xF)
            my_printf("0");
        my_printf("%X", arena->ram[i]);
    }
    my_printf("\n");
    return 1;
}

static int find_winner(arena_t *arena)
{
    int bestest = 0;
    int id = 0;

    for (uint32_t i = 0; i < arena->programs_count; i++) {
        if (arena->programs[i].cycles_before_die > bestest &&
            !arena->programs[i].is_dead) {
            bestest = arena->programs[i].cycles_before_die;
            id = arena->programs[i].id;
        }
    }
    return id;
}

static int check_end(arena_t *arena)
{
    int alive = 0;

    for (uint32_t i = 0; i < arena->programs_count; i++)
        alive += arena->programs[i].is_dead == false;
    return alive <= 1;
}

static int run_cycle(arena_t *arena)
{
    for (uint32_t i = 0; i < arena->programs_count && show_mem(arena); i++) {
        arena->programs[i].cycles_before_die--;
        arena->programs[i].cycles_before_next_instruction--;
        if (arena->programs[i].cycles_before_die <= 0)
            arena->programs[i].is_dead = true;
        if (arena->programs[i].cycles_before_next_instruction > 0 ||
            arena->programs[i].is_dead)
            continue;
        if (execute_next_inst(arena, &arena->programs[i]) ==
            69) {
            arena->exit_code = EXIT_FAILURE_TECH;
            return 1;
        }
    }
    if (arena->current_cycle == arena->cycle_to_dump)
        return dump_cycle(arena);
    if (check_end(arena))
        return 1;
    arena->current_cycle++;
    return 0;
}

int corewar(int argc, char const **argv)
{
    arena_t arena;
    int ret;

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return print_help();
    if (VISUAL_MODE == 1)
            init_ncurses();
    if (create_arena(&arena) || parse_arguments(argc, argv, &arena))
        return EXIT_FAILURE_TECH;
    if (create_arena_memory(&arena))
        return EXIT_FAILURE_TECH;
    while (run_cycle(&arena) != 1);
    my_printf("The player %d(%s) has won.\n", find_winner(&arena),
        arena.programs[find_winner(&arena)].name);
    ret = arena.exit_code;
    free_arena(&arena);
    return ret;
}
