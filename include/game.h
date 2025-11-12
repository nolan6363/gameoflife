#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum boundary_types {
    EDGE,
    TORUS,
    MIRROR,
    RIM
};

typedef struct {
    uint64_t * bit_array;
    size_t width;
    size_t height;
} World;

World * allocate_world(size_t w, size_t h);
void load_world_from_file(World *world, const char *filename);
void print_game_state(World * world);
void print_game_state_debug(World * world); 
bool get_cell_state(World * world, int x, int y);
void set_cell_state(World * world, int x, int y, bool value);
int num_neighbors(World * world, enum boundary_types boundaries, int x, int y);
bool get_next_state(World * world, enum boundary_types boundaries, int x, int y);
void next_generation(World * world, World * buffer, enum boundary_types boundaries);

#endif
