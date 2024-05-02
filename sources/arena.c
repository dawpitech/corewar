/*
** EPITECH PROJECT, 2024
** arena
** File description:
** title
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "op.h"
#include "corewar.h"
#include "arena.h"
#include "my.h"
#include <endian.h>
#include <sys/types.h>
#include <sys/stat.h>

static int copy_champs_internal(arena_t *arena, int i, char *buff,
    long *last_addr)
{
    if (arena->programs[i].program_counter != 0) {
        my_memcpy(buff,
            arena->programs[i].size - sizeof(header_t),
            &arena->ram[arena->programs[i].program_counter]);
    }
    if (arena->programs[i].program_counter == 0) {
        my_memcpy(buff, arena->programs[i].size - sizeof(header_t),
            &arena->ram[*last_addr]);
        arena->programs[i].program_counter = *last_addr;
        return 1;
    }
    free(buff);
    fclose(arena->programs[i].fp);
    return 0;
}

static int init_copy(char **buff, int i, arena_t *arena)
{
    *buff = malloc(arena->programs[i].size);
    if (*buff == NULL)
        return 1;
    fread(*buff, arena->programs[i].size, 1, arena->programs[i].fp);
    if (arena->programs[i].program_counter != 0 &&
        arena->programs[i].program_counter >= MEM_SIZE)
        return 1;
    return 0;
}

static int copy_champs(arena_t *arena)
{
    char *buff = NULL;
    long tot_size = 0;
    long distance = 0;
    long last_addr = 0;

    for (int j = 0; j < MAX_ARGS_NUMBER; j++)
        if (arena->programs[j].name != NULL)
            tot_size += (arena->programs[j].size - sizeof(header_t));
    distance = (MEM_SIZE - tot_size) / arena->programs_count;
    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        if (arena->programs[i].name == NULL)
            continue;
        if (init_copy(&buff, i, arena))
            return 1;
        if (copy_champs_internal(arena, i, buff, &last_addr))
            last_addr += distance;
    }
    return 0;
}

static int check_champion(header_t *header, struct stat *s, FILE *f,
    program_t *program)
{
    my_memset(header, 0, sizeof(*header));
    fread(header, sizeof(*header), 1, f);
    if (header->magic != (int)htobe32(COREWAR_EXEC_MAGIC))
        return 1;
    if (htobe32(header->prog_size) != (s->st_size - sizeof(header_t)))
        return 1;
    if ((s->st_size - sizeof(header_t)) >= MEM_SIZE)
        return 1;
    free(program->name);
    return 0;
}

int create_arena_memory(arena_t *arena)
{
    struct stat s;
    FILE *f = 0;
    header_t header;

    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        if (arena->programs[i].name == NULL)
            continue;
        if (stat(arena->programs[i].name, &s) == -1)
            return 1;
        f = fopen(arena->programs[i].name, "rb");
        if (f == NULL)
            return 1;
        if (check_champion(&header, &s, f, &arena->programs[i]))
            return 1;
        arena->programs[i].name = my_strdup(header.prog_name);
        arena->programs[i].registers[0] = i;
        arena->programs[i].fp = f;
        arena->programs[i].size = s.st_size;
    }
    return copy_champs(arena);
}

void free_arena(arena_t *arena)
{
    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        if (arena->programs[i].name == NULL)
            continue;
        free(arena->programs[i].name);
    }
}
