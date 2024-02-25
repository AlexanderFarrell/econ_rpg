//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_WINDOW_H
#define ECON_RPG_WINDOW_H

#include <SDL2/SDL.h>

#define WINDOW_ERROR (1 << 0)

typedef struct Window Window;
struct Window {
    SDL_Window* sdl_window;
    float scale;
    int width;
    int height;
    char flags;
};

extern Window window;

// Creates a new window. If this fails to create an initial window, it will close the app.
void window_start(int width, int height, char * graphics_api, char * title);

void window_set_title(const char * title);

// Attempts to swap the current window with another of a different graphics_api.
// If this fails, it will keep the current window.
void window_swap_graphics_api(char * graphics_api);

//
void window_end();

#endif //ECON_RPG_WINDOW_H
