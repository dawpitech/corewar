/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include <stdint.h>
#include <stdbool.h>

#include "op.h"

#ifndef COREWAR_COREWAR_H
    #define COREWAR_COREWAR_H
    #define EXIT_SUCCESS_TECH 0
    #define EXIT_FAILURE_TECH 84
typedef struct {
    char *name;
    uint32_t program_counter;
    int32_t registers[REG_NUMBER];
    uint8_t cycles_before_next_instruction;
    uint32_t cycles_before_die;
    uint8_t carry_bit;
    bool is_dead;
} program_t;
typedef struct {
    uint8_t cycle_to_dump;
    uint8_t current_cycle;
    uint8_t ram[MEM_SIZE];
    uint8_t programs_count;
    program_t programs[MAX_ARGS_NUMBER];
} arena_t;
int corewar(int argc, char const **argv);
int execute_next_inst(arena_t *arena, program_t *program);
uint8_t *decode_cb(arena_t *arena, uint32_t address);
uint32_t read_uint32(arena_t *arena, uint32_t address);
#endif //COREWAR_COREWAR_H
