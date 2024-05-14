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
    bool carry_bit;
    bool is_dead;
    int id;
    FILE *fp;
    long size;
} program_t;
typedef struct {
    long cycle_to_dump;
    long current_cycle;
    uint8_t ram[MEM_SIZE];
    uint8_t programs_count;
    int exit_code;
    program_t *programs;
} arena_t;
typedef struct {
    int value;
    size_t size;
} param_t;
typedef struct {
    uint8_t instruction;
    uint8_t coding_byte;
    param_t params[4];
} instruct_infos_t;
int corewar(int argc, char const **argv);
int execute_next_inst(arena_t *arena, program_t *program);
int execute_fork(arena_t *arena, program_t *program);
int execute_lfork(arena_t *arena, program_t *program);
void write_bytes(long num, int byte_nb, uint32_t address, arena_t *arena);
uint8_t *decode_cb(arena_t *arena, uint32_t address);
int16_t read_int16(arena_t *arena, uint32_t address);
uint8_t read_uint8(arena_t *arena, uint32_t address);
uint16_t read_uint16(arena_t *arena, uint32_t address);
uint32_t read_uint32(arena_t *arena, uint32_t address);
instruct_infos_t *decode_instruction(arena_t *arena, uint32_t *address);
#endif //COREWAR_COREWAR_H
