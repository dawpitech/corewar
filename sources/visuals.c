/*
** EPITECH PROJECT, 2024
** visuals
** File description:
** title
*/

#include "corewar.h"
#include "my.h"
#include "visuals.h"
#include <ncurses.h>
#include <stdint.h>
#include <unistd.h>

int init_ncurses(void)
{
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_BLUE, -1);
    init_pair(6, COLOR_CYAN, -1);
    init_pair(7, COLOR_MAGENTA, -1);
    return 0;
}

static int find_pc(uint32_t x, arena_t *arena)
{
    for (uint32_t i = 0; i < arena->programs_count; i++) {
        if (x == arena->programs[i].program_counter &&
            !arena->programs[i].is_dead) {
            return 1;
        }
    }
    return 0;
}

static int in_buffer(uint32_t count, arena_t *arena, program_t *program,
    int buff[arena->programs_count])
{
    for (uint32_t j = 0; j < count; j++) {
        if (program->id == buff[j])
            return 1;
    }
    return 0;
}

static int is_prog_dead(arena_t *arena, int id)
{
    for (uint32_t i = 0; i < arena->programs_count; i++) {
        if (id == arena->programs[i].id &&
            !arena->programs[i].is_dead)
            return 0;
    }
    return 1;
}

static int show_header(arena_t *arena, int cols)
{
    int buff[arena->programs_count];
    uint32_t count = 0;
    int gap = (cols - 5) / MAX_ARGS_NUMBER;
    int dead = 0;
    int y = 5;

    mvprintw(0, 0, "Cycle: %ld", arena->current_cycle);
    my_memset(buff, -1, arena->programs_count * sizeof(int));
    for (uint32_t i = 0; i < arena->programs_count; i++) {
        if (!in_buffer(count, arena, &arena->programs[i], buff)) {
            buff[count] = arena->programs[i].id;
            attron(COLOR_PAIR(4 + arena->programs[i].id));
            mvprintw(2, y, "%s", arena->programs[i].name);
            attroff(COLOR_PAIR(4 + arena->programs[i].id));
            mvprintw(2, y + my_strlen(arena->programs[i].name), " - ");
            dead = is_prog_dead(arena, arena->programs[i].id);
            attron(COLOR_PAIR(2 + dead));
            mvprintw(2, y + my_strlen(arena->programs[i].name) + 3, "%s",
                dead ? "Dead" : "Alive");
            attroff(COLOR_PAIR(2 + dead));
            y += gap;
            count++;
        }
    }
    return 0;
}

int show_mem(arena_t *arena)
{
    uint32_t x = 0;
    uint32_t y = 5;
    int rows = 0;
    int cols = 0;
    int id = 0;

    getmaxyx(stdscr, rows, cols);
    clear();
    show_header(arena, cols);
    for (uint32_t i = 0; i < MEM_SIZE; i++) {
        if (i != 0 && i % cols == 0) {
            y++;
            x = 0;
        }
	id = arena->ram_owning[i];
	if (id != -1)
	    attron(COLOR_PAIR(4 + id));
        mvprintw(y, x, "%02X", arena->ram[i]);
	if (id != -1)
	    attroff(COLOR_PAIR(4 + id));
        if (find_pc(i, arena)) {
            attron(COLOR_PAIR(1));
            mvprintw(y, x, "%02X", arena->ram[i]);
            attroff(COLOR_PAIR(1));
        }
        x++;
    }
    refresh();
    usleep(500);
    return 1;
}
