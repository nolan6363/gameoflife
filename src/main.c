#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

enum boundary_types {
    EDGE,
    TORUS,
    MIRROR,
    RIM
};

int main(int argc, char ** argv) {
    // Récupérer les arguments 
    int width = 320;
    int height = 240;
    int generations = 500;
    int boundaries = EDGE;
    char * input_file = NULL;
    char * output_file = NULL;
    int target_hz = 60;

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--width") == 0 && i + 1 < argc) {
            width = atoi(argv[i + 1]); 
        } else if (strcmp(argv[i], "--height") == 0 && i + 1 < argc) {
            height = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--gens") == 0 && i + 1 < argc) {
            generations = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "--boundary") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "edge") == 0) {
                boundaries = EDGE;
            } else if (strcmp(argv[i + 1], "torus") == 0) {
                boundaries = TORUS;
            } else if (strcmp(argv[i + 1], "mirror") == 0) {
                boundaries = MIRROR;
            } else if (strcmp(argv[i + 1], "rim") == 0) {
                boundaries = RIM;
            } else {
                printf("ERROR : invalid syntax for parameter \"--boundary\"\n");
                printf("Accepted values : edge, torus, mirror, rim\n");
                exit(-1);
            }
        } else if (strcmp(argv[i], "--in") == 0 && i + 1 < argc) {
            input_file = argv[i + 1];
        } else if (strcmp(argv[i], "--out") == 0 && i + 1 < argc) {
            output_file = argv[i + 1];
        } else if (strcmp(argv[i], "--target_hz") == 0 && i + 1 < argc) {
            target_hz = atoi(argv[i + 1]);
        }   
    }

    World * world = allocate_world(width, height);
    print_game_state(world);
    return 0;
}

