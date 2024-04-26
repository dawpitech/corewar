/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include "corewar.h"
#include "my.h"
#include "op.h"

static int print_help(void)
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

int corewar(int argc, char const **argv)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return print_help();
    return EXIT_SUCCESS_TECH;
}
