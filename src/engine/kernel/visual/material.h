//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_MATERIAL_H
#define ECON_RPG_MATERIAL_H

#include "shader.h"
#include "uniform.h"
#include "texture.h"

#define MATERIAL_FREE_TEXTURE (2 << 0)
#define MATERIAL_FREE_MATERIAL (2 << 1)

typedef struct Material Material;
struct Material {
    void * shader;
    Uniform* uniforms;
    Texture ** textures;
    int uniform_count;
    int texture_count;
    int uniform_capacity;
    int texture_capacity;
    uint8_t flags;
};

Material * material_new(void * shader);
void material_delete(Material * material);
void material_prepare(Material * material);
void material_add_uniform(Material * material, Uniform uniform);
void material_add_texture(Material * material, Texture * texture);

#endif //ECON_RPG_MATERIAL_H
