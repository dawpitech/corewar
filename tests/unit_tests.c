/*
** EPITECH PROJECT, 2024
** PLACEHOLDER
** File description:
** PLACEHOLDER
*/

#include <criterion/criterion.h>

#include "../include/corewar.h"

Test(unit, cb_decoder) {
    arena_t arena = {0};
    arena.ram[0] = 0x90;
    uint8_t *types;

    types = decode_cb(&arena, 0);
    cr_expect_eq(types[0], T_DIR);
    cr_expect_eq(types[1], T_REG);
    cr_expect_eq(types[2], 0);
    cr_assert_eq(types[3], 0);
}

Test(unit, instruction_decoder) {
    arena_t arena = {0};
    uint32_t addr = 0;
    arena.ram[0] = 0x02;
    arena.ram[1] = 0x90;
    arena.ram[2] = 0x00;
    arena.ram[3] = 0x00;
    arena.ram[4] = 0x00;
    arena.ram[5] = 0x00;
    arena.ram[6] = 0x03;
    instruct_infos_t *infos;

    infos = decode_instruction(&arena, &addr);
    cr_expect_eq(infos->instruction, 0x02);
    cr_expect_eq(infos->coding_byte, 0x90);
    cr_expect_eq(infos->params[0].value, 0);
    cr_expect_eq(infos->params[0].size, T_DIR);
    cr_expect_eq(infos->params[1].value, 3);
    cr_expect_eq(infos->params[1].size, T_REG);
    cr_expect_eq(infos->params[2].size, 0);
    cr_assert_eq(infos->params[3].size, 0);
}