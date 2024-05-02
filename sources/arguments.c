/*
** EPITECH PROJECT, 2024
** args
** File description:
** title
*/

#include <stddef.h>
#include "corewar.h"
#include "arguments.h"
#include "my.h"
#include "op.h"
#include <stdio.h>

int print_help(void)
{
    my_putstr("USAGE\n./corewar [-dump nbr_cycle] [[-n prog_number] [-a load");
    my_putstr("_address] prog_name] ...\nDESCRIPTION\n-dump nbr_cycle dumps");
    my_putstr(" the memory after the nbr_cycle execution (if the round isn't");
    my_putstr(" already over) with the following format: 32 bytes/line in ");
    my_putstr("hexadecimal (A0BCDEFE1DD3...)\n-n prog_number sets the next ");
    my_putstr("program's number. By default, the first free number in the");
    my_putstr(" parameter order\n-a load_address sets the next program's ");
    my_putstr("loading address. When no address is specified, optimize the ");
    my_putstr("addresses so that the processes are as far away from each ");
    my_putstr("other as possible. The addresses are MEM_SIZE modulo.\n");
    return EXIT_SUCCESS_TECH;
}

static int is_nbr_valid(const char *nbr)
{
    for (int i = 0; nbr[i] != '\0'; i++)
        if (!IS_NUM(nbr[i]))
            return 0;
    return 1;
}

static int get_nbr_or_addr(const char **argv, int *i, long *nbr, long *addr)
{
    if (my_strcmp(argv[*i], "-n") == 0) {
        *nbr = my_getnbr(argv[*i + 1]);
        *i += 2;
        return 1;
    }
    if (my_strcmp(argv[*i], "-a") == 0) {
        *addr = my_getnbr(argv[*i + 1]);
        *i += 2;
        return 1;
    }
    return 0;
}

static int find_place(arena_t *arena, long *nbr)
{
    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        if (arena->programs[i].name == NULL) {
            *nbr = i;
            return 1;
        }
    }
    return 1;
}

static int parse_program(int argc, const char **argv, arena_t *arena, int *i)
{
    long nbr = 0;
    long addr = 0;

    while (*i < argc) {
        if ((my_strcmp(argv[*i], "-n") == 0 || my_strcmp(argv[*i], "-a") == 0)
            && ((*i + 1) >= argc || !is_nbr_valid(argv[*i + 1])))
            return 1;
        if (find_place(arena, &nbr) && get_nbr_or_addr(argv, i, &nbr, &addr))
            continue;
        if (arena->programs[nbr].name != NULL)
            return 1;
        arena->programs_count++;
        arena->programs[nbr].name = my_strdup(argv[*i]);
        arena->programs[nbr].program_counter = addr;
        break;
    }
    return 0;
}

int parse_arguments(int argc, const char **argv, arena_t *arena)
{
    int i = 1;

    while (i < argc) {
        if (my_strcmp(argv[i], "-dump") == 0 && (i + 1) >= argc)
            return 1;
        if (my_strcmp(argv[i], "-dump") == 0) {
            arena->cycle_to_dump = my_getnbr(argv[i + 1]);
            i += 2;
            continue;
        }
        if (parse_program(argc, argv, arena, &i))
            return 1;
        ++i;
    }
    return 0;
}
