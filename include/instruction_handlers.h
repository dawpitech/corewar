/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#pragma once
#include "corewar.h"
#define INSTRUCTION_HANDLERS_SIZE (5)

typedef struct {
    int instruction_code;
    int (*handler)(arena_t *arena, program_t *program);
} instruction_handler_t;

static
const instruction_handler_t instruction_handlers[] = {
    {0x01, execute_live},
    {0x02, execute_ld},
    {0x03, execute_st},
    {0x04, execute_add},
    {0x05, execute_sub},
    {0x06, execute_and},
    {0x07, execute_or},
    {0x08, execute_xor},
    {0x09, execute_zjmp},
    {0x0A, execute_ldi},
    {0x0B, execute_sti},
    {0x0C, execute_fork},
    {0x0D, execute_lld},
    {0x0E, execute_lldi},
    {0x0F, execute_lfork},
    {0x10, execute_aff},
};
