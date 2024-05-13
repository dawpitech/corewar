/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include <malloc.h>
#include <sys/types.h>

#include "corewar.h"

static
int read_value(arena_t *arena, uint32_t address, size_t size)
{
    switch (size) {
        case 1:
            return (int) read_uint8(arena, address);
        case 2:
            return (int) htobe16(read_uint16(arena, address));
        case 4:
            return (int) htobe32(read_uint32(arena, address));
        default:
            return 0;
    }
}

static
void read_params(arena_t *arena, uint32_t *address, instruct_params_t *params, const uint8_t *params_type)
{
    params->p1_size = params_type[0];
    params->p1_value = read_value(arena, *address, params->p1_size);
    *address += params->p1_size;
    params->p2_size = params_type[1];
    params->p2_value = read_value(arena, *address, params->p2_size);
    *address += params->p2_size;
    params->p3_size = params_type[2];
    params->p3_value = read_value(arena, *address, params->p3_size);
    *address += params->p3_size;
    params->p4_size = params_type[3];
    params->p4_value = read_value(arena, *address, params->p4_size);
    *address += params->p4_size;
}

instruct_params_t *decode_instruction(arena_t *arena, uint32_t *address)
{
    instruct_params_t *params = calloc(1, sizeof(instruct_params_t));
    uint8_t *params_type;

    params->instruction = read_uint8(arena, *address);
    *address += 1;
    params->coding_byte = read_uint8(arena, *address);
    params_type = decode_cb(arena, *address);
    *address += 1;
    read_params(arena, address, params, params_type);
    free(params_type);
    return params;
}
