//
// Created by alexander on 2/24/24.
//

#include "kernel.h"
#include "../core/app.h"
#include "../core/config.h"
#include "window/window.h"
#include "visual/visual.h"
#include "console/console.h"


typedef struct Kernel Kernel;
struct Kernel {
    unsigned long step;
    int (*poll_event_func)(SDL_Event * event);

};

Kernel kernel = {0};

void kernel_start() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        app_panic("Could not initialize SDL: %s\n", SDL_GetError());
    }
    kernel.poll_event_func = SDL_PollEvent;

    char * graphics_api = config_get_str("graphics_api");

    window_start(
        config_get_int("window_width"),
        config_get_int("window_height"),
        graphics_api,
        config_get_str("name")
    );

    visual_start(graphics_api);
}

void kernel_update() {
    SDL_Event event;
    visual_update();
    while (kernel.poll_event_func(&event)) {
        if (event.type == SDL_QUIT) {
            app_stop();
            break;
        }
        switch (event.type) {
//            case SDL_QUIT:
//                app_stop();
//                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_MOUSEWHEEL:
                break;
            case SDL_TEXTINPUT:
                break;
            case SDL_MOUSEMOTION:
                break;
        }
    }

    visual_update_late();
    SDL_Delay(10);
    kernel.step++;
}

void kernel_end() {
    visual_end();
    window_end();
    SDL_Quit();
}

void kernel_set_poll_func(int (*poll_event_func)(SDL_Event * event)) {
    if (poll_event_func == SDL_PollEvent) {
        kernel.poll_event_func = SDL_PollEvent;
    } else if (poll_event_func == SDL_WaitEvent) {
        kernel.poll_event_func = SDL_WaitEvent;
    } else {
        log_error("Failed to switch poll_event_func, unrecognized poll event func: %p - "
                  "Please pass either SDL_PollEvent or SDL_WaitEvent.\n"
            , poll_event_func);
    }
}

unsigned long get_step() {
    return kernel.step;
}