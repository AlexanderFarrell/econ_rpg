//
// Created by alexander on 2/24/24.
//

#include "window.h"
#include <string.h>
#include "../console/console.h"
#include "../../core/app.h"
#include "../../core/config.h"

Window window = {0};

int window_get_graphics_api_flag(char * graphics_api);
Window window_new(int width, int height, char * graphics_api, char * title);
void window_breakdown(Window* w);

void window_start(int width, int height, char * graphics_api, char * title) {
    window = window_new(width, height, graphics_api, title);
    if (window.flags & WINDOW_ERROR) {
        app_panic("Failed to create initial window\n");
    }
}

void window_swap_graphics_api(char * graphics_api) {
    // If we don't have a window yet, crash
    if (window.sdl_window == NULL) {
        app_panic("Cannot swap graphics_api. No window exists. First call window_start()");
    }

    const char * window_title_const = SDL_GetWindowTitle(window.sdl_window);
    char * window_title = malloc(strnlen(window_title_const, 100));

    Window future_window = window_new(
        window.width,
        window.height,
        graphics_api,
        window_title
    );

    free(window_title);

    if (future_window.flags != WINDOW_ERROR) {
        window_breakdown(&window);
        window = future_window;
        log_info("Created new window for %s\n", graphics_api);
    } else {
        log_error("Failed to create new window with graphics_api: %s\n", graphics_api);
    }
}

void window_end() {
    window_breakdown(&window);
}

Window window_new(int width, int height, char * graphics_api, char * title) {
    int sdl_window_flags = window_get_graphics_api_flag(graphics_api);
    if (sdl_window_flags == 0) {
        log_error("Failed to create window with renderer: %s \n", graphics_api);
        window.flags = WINDOW_ERROR;
        return window;
    }
    sdl_window_flags |= SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    window.width = width;
    window.height = height;

    window.sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        sdl_window_flags
    );

    if (!window.sdl_window) {
        log_error("Failed to open window: %s \n", SDL_GetError());
        window.flags = WINDOW_ERROR;
        return window;
    }

    int w, h;
    SDL_GL_GetDrawableSize(window.sdl_window, &w, &h);
    window.scale = (float)w/(float)window.width;
    return window;
}

void window_breakdown(Window* w) {
    SDL_DestroyWindow(w->sdl_window);
    w->sdl_window = NULL;
    w->width = 0;
    w->height = 0;
    w->flags = 0;
}

int window_get_graphics_api_flag(char * graphics_api) {
    if (strncmp(graphics_api, "opengl", 20) == 0) {
        return SDL_WINDOW_OPENGL;
    } else if (strncmp(graphics_api, "vulkan", 20) == 0) {
        return SDL_WINDOW_VULKAN;
    } else if (strncmp(graphics_api, "metal", 20) == 0) {
        return SDL_WINDOW_METAL;
    } else if (strncmp(graphics_api, "directx12", 20) == 0) {
        log_error("Graphics API not supported yet: %s\n", graphics_api);
        return 0;
    } else if (strncmp(graphics_api, "directx11", 20) == 0) {
        log_error("Graphics API not supported yet: %s\n", graphics_api);
        return 0;
    } else if (strncmp(graphics_api, "software", 20) == 0) {
        log_error("Graphics API not supported yet: %s\n", graphics_api);
        return 0;
    } else {
        log_error("Unknown graphics_api: %s\n", graphics_api);
        return 0;
    }
}

int window_flag_from_config() {
    char * graphics_api = config_get_str("graphics_api");
    return window_get_graphics_api_flag(graphics_api);
}

