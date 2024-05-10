/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "op.h"

#ifndef COREWAR_COREWAR_H
    #define COREWAR_COREWAR_H
    #define EXIT_SUCCESS_TECH 0
    #define EXIT_FAILURE_TECH 84
typedef struct {
    char *name;
    uint32_t program_counter;
    int32_t registers[REG_NUMBER];
    long cycles_before_next_instruction;
    long cycles_before_die;
    uint8_t carry_bit;
    bool is_dead;
    FILE *fp;
    long size;
} program_t;
typedef struct {
    long cycle_to_dump;
    long current_cycle;
    uint8_t ram[MEM_SIZE];
    uint8_t programs_count;
    int exit_code;
    program_t programs[MAX_ARGS_NUMBER];
} arena_t;
int corewar(int argc, char const **argv);
int execute_next_inst(arena_t *arena, program_t *program);
uint8_t *decode_cb(arena_t *arena, uint32_t address);
uint32_t read_uint32(arena_t *arena, uint32_t address);
#endif //COREWAR_COREWAR_H
