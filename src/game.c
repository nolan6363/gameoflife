#include "game.h"

World * allocate_world(size_t w, size_t h) {
    int n_uint = ((w * h) + 64 - 1) / 64; 
   
    World * world = (World *) malloc(sizeof(World));

    world->bit_array = (uint64_t *) malloc(n_uint * sizeof(uint64_t));
    world->width = w;
    world->height = h;

    //world->bit_array[3] = 0b0101010101010101010101010101010101010101010101010101010101010101;

    return world;
}

void print_game_state(World * world) {
    int i = 0;
    char * game_state = (char *) malloc((world->width + 2) * sizeof(char));
    
    for (int h = 0; h < world->height; h++) {
        for (int w = 0; w < world->width; w++) {
            game_state[w] = ((world->bit_array[i >> 6] >> (i & 63)) & 1)? '#': ' ';
            i++;
        }
        printf("%s\n", game_state);
    }
}

bool get_cell_state(World * world, int x, int y) {
    return false;
}

int num_neighbors(World * world, int x, int y) {
    return 0;
}

bool get_next_state(World * world, int x, int y) {
    return false;
}

void next_generation(World * world) {

}

