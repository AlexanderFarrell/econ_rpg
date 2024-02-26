//
// Created by alexander on 2/20/24.
//

#ifndef ECONOMICS_SIMULATOR_GRAPHICS_API_H
#define ECONOMICS_SIMULATOR_GRAPHICS_API_H

#include "uniform.h"

typedef struct GraphicsApi GraphicsApi;
struct GraphicsApi {
    void * context;
    void (*init)();
    void (*update)();
    void (*update_late)();
    void (*breakdown)();
    void * (*shader_from_sources)(char * vert_source, char * frag_source);
    void (*shader_use)(void * shader);
    void (*shader_delete)(void * shader);
    void (*uniform_prepare)(Uniform* uniform, void * shader);
    void (*uniform_bind)(Uniform * uniform);
};

#endif //ECONOMICS_SIMULATOR_GRAPHICS_API_H
