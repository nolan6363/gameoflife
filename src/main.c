#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

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
    World * buffer = allocate_world(width, height);
    
    if (input_file) load_world_from_file(world, input_file);

//    print_game_state(world);
    
    clock_t t; 
    t = clock();

    for (int i = 0; i < generations / 2; i++) {
        next_generation(world, buffer, boundaries);
//        print_game_state(buffer);
        next_generation(buffer, world, boundaries);
//        print_game_state(world);
    }

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    
    printf("%d generations took %f seconds to execute \n", generations, time_taken); 
    printf("This is %f ms per generations, %f FPS. \n", time_taken / generations * 1000.0f, 1.0f / (time_taken / generations));
    
//    print_game_state(world);
    return 0;
}

