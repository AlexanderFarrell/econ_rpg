//
// Created by alexander on 2/20/24.
//

#ifndef ECONOMICS_SIMULATOR_GRAPHICS_API_H
#define ECONOMICS_SIMULATOR_GRAPHICS_API_H

typedef struct GraphicsApi GraphicsApi;
struct GraphicsApi {
    void * context;
    void (*init)();
    void (*update)();
    void (*update_late)();
    void (*breakdown)();
};

#endif //ECONOMICS_SIMULATOR_GRAPHICS_API_H
