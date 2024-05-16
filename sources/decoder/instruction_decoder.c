/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include <endian.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>

#include "corewar.h"

static
int read_value(arena_t *arena, uint32_t *address, size_t type)
{
    int rt_value;

    switch (type) {
        case 1:
            rt_value = read_uint8(arena, *address);
            *address += 1;
            return rt_value;
        case 2:
            rt_value = htobe32(read_uint32(arena, *address));
            *address += 4;
            return rt_value;
        case 4:
            rt_value = htobe16(read_uint16(arena, *address));
            *address += 2;
            return rt_value;
        default:
            return -1;
    }
}

static
void read_params(arena_t *arena, uint32_t *address,
    instruct_infos_t *params, bool is_index)
{
    uint8_t *params_type = decode_cb(arena, *address);
    size_t param_type;

    *address += 1;
    for (int i = 0; i < 4; i++) {
        param_type = params_type[i];
        if (is_index && param_type == T_DIR)
            param_type = T_IND;
        params->params[i].value = read_value(arena, address, param_type);
        params->params[i].size = param_type;
    }
    free(params_type);
}

static bool is_index_instruction(instruct_infos_t *infos)
{
    return (infos->instruction == 0x0A || infos->instruction == 0x0B ||
            infos->instruction == 0x0E);
}

instruct_infos_t *decode_instruction(arena_t *arena, uint32_t *address)
{
    instruct_infos_t *infos = malloc(sizeof(instruct_infos_t));

    infos->instruction = read_uint8(arena, *address);
    *address += 1;
    infos->coding_byte = read_uint8(arena, *address);
    read_params(arena, address, infos, is_index_instruction(infos));
    return infos;
}
