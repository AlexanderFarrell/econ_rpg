//
// Created by alexander on 2/20/24.
//

#ifndef ECONOMICS_SIMULATOR_GRAPHICS_API_H
#define ECONOMICS_SIMULATOR_GRAPHICS_API_H

#include "uniform.h"
#include "texture.h"
#include "mesh.h"

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
    void (*texture_buffer)(Texture* texture);
    void (*texture_activate)(Texture* texture, int n);
    void (*texture_destroy)(Texture* texture);
    void (*mesh_init)(Mesh* mesh);
    void (*mesh_deinit)(Mesh* mesh);
    void (*mesh_draw)(Mesh* mesh);
    size_t texture_size;
    size_t mesh_size;
};

#endif //ECONOMICS_SIMULATOR_GRAPHICS_API_H
