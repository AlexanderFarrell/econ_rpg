//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_KERNEL_H
#define ECON_RPG_KERNEL_H

#include <SDL2/SDL.h>

void kernel_start();
void kernel_update();
void kernel_end();
void kernel_set_poll_func(int (*poll_event_func)(SDL_Event * event));

// Gets the number of game frames which have passed since the programs start.
unsigned long get_step();

#endif //ECON_RPG_KERNEL_H
