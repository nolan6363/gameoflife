#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t * bit_array;
    size_t width;
    size_t height;
} World;

World * allocate_world(size_t w, size_t h);
void print_game_state(World * world);
bool get_cell_state(World * world, int x, int y);
int num_neighbors(World * world, int x, int y);
bool get_next_state(World * world, int x, int y);
void next_generation(World * world);

#endif
