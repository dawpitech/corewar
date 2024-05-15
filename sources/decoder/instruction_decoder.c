/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar header
*/

#include <endian.h>
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
void read_params(arena_t *arena, uint32_t *address,
    instruct_infos_t *params, bool is_index)
{
    uint8_t *params_type = decode_cb(arena, *address);
    size_t size_to_read;

    *address += 1;
    for (int i = 0; i < 4; i++) {
        size_to_read = params_type[i];
        if (!is_index && size_to_read == T_DIR)
            size_to_read = T_IND;
        params->params[i].value = read_value(arena, *address, size_to_read);
        params->params[i].size = size_to_read;
        *address += size_to_read;
    }
    free(params_type);
}

static
bool is_index_instruction(instruct_infos_t *infos) {
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
