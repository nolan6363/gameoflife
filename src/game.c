#include "game.h"

World * allocate_world(size_t w, size_t h) {
    int n_uint = ((w * h) + 64 - 1) / 64; 
   
    World * world = (World *) malloc(sizeof(World));

    world->bit_array = (uint64_t *) malloc(n_uint * sizeof(uint64_t));
    world->width = w;
    world->height = h;

    return world;
}

void load_world_from_file(World *world, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        return;
    }

    char line[1024];
    int y = 0;
    
    while (fgets(line, sizeof(line), file) && y < world->height) {
        for (int x = 0; x < world->width && x < strlen(line); x++) {
            if (line[x] == '*') {
                set_cell_state(world, x, y, true);
            } else if (line[x] == '.') {
                set_cell_state(world, x, y, false);
            }
        }
        y++;
    }

    fclose(file);
}

void print_game_state(World * world) {
    int i = 0;
    char * game_state = (char *) malloc((world->width + 2) * sizeof(char));
    
    printf("+");
    for (int w = 0; w < world->width; w++) {
       printf("-"); 
    }
    printf("+\n");
    for (int h = 0; h < world->height; h++) {
        printf("|");
        for (int w = 0; w < world->width; w++) {
            game_state[w] = ((world->bit_array[i >> 6] >> (i & 63)) & 1)? '#': ' ';
            i++;
        }
        game_state[world->width] = '\0';
        printf("%s", game_state);
        printf("|\n");
    }
    printf("+");
    for (int w = 0; w < world->width; w++) {
       printf("-"); 
    }
    printf("+\n");
}

void print_game_state_debug(World * world) {
    int i = 0;
    char * game_state = (char *) malloc((world->width + 2) * sizeof(char));
    
    printf("  +");
    for (int w = 0; w < world->width; w++) {
        printf("%d", w); 
    }
    printf("+\n");
    for (int h = 0; h < world->height; h++) {
        if(h < 10) printf(" %d|", h);
        else printf("%d|", h);
        for (int w = 0; w < world->width; w++) {
            game_state[w] = 48 + num_neighbors(world, EDGE, w, h); 
            i++;
        }
        printf("%s", game_state);
        printf("|\n");
    }
    printf("+");
    for (int w = 0; w < world->width; w++) {
       printf("-"); 
    }
    printf("+\n");
}

bool get_cell_state(World * world, int x, int y) {
    int bit_pos = y * world->width + x;
    return ((world->bit_array[bit_pos >> 6] >> (bit_pos & 63)) & 1)? true: false;
}

void set_cell_state(World * world, int x, int y, bool value) {
    int bit_pos = y * world->width + x;
    if (value) {
        world->bit_array[bit_pos >> 6] |= ((uint64_t)1 << (bit_pos & 63));
    } else {
        world->bit_array[bit_pos >> 6] &= ~((uint64_t)1 << (bit_pos & 63));
    }
}

int num_neighbors(World * world, enum boundary_types boundaries, int x, int y) {
    int num = 0;
    switch (boundaries) {
        case EDGE:
            if (y - 1 >= 0) {
                if (x - 1 >= 0) num += (int) get_cell_state(world, x - 1, y - 1);
                num += (int) get_cell_state(world, x, y - 1);
                if (x + 1 < world->width) num += (int) get_cell_state(world, x + 1, y - 1);
            }
            if (y + 1 < world->height) {
                if (x - 1 >= 0) num += (int) get_cell_state(world, x - 1, y + 1);
                num += (int) get_cell_state(world, x, y + 1);
                if (x + 1 < world->width) num += (int) get_cell_state(world, x + 1, y + 1);
            }
            if (x - 1 >= 0) {
                num += (int) get_cell_state(world, x - 1, y);
            }
            if (x + 1 < world->width) {
                num += (int) get_cell_state(world, x + 1, y);
            }
            break;
        default:
            break;
    }
    return num;
}

bool get_next_state(World * world, enum boundary_types boundaries, int x, int y) {
    if (num_neighbors(world, boundaries, x, y) == 3) {
        return true;
    } else if (get_cell_state(world, x, y) && (num_neighbors(world, boundaries, x, y) == 2)) {
        return true;
    } else {
        return false;
    }
}

void next_generation(World * world, World * buffer, enum boundary_types boundaries) {
    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            set_cell_state(buffer, x, y, get_next_state(world, boundaries, x, y));
        }
    }
}

