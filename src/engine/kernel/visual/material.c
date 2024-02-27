//
// Created by alexander on 2/26/24.
//

#include "material.h"
#include <stdlib.h>
#include "../../core/app.h"

void material_init(Material* material, void * shader) {
    material->shader = shader;
    material->uniforms = malloc(sizeof(Uniform) * 1);
    material->uniform_count = 0;
    material->uniform_capacity = 1;

    material->textures = malloc(sizeof(Texture*) * 1);
    material->texture_count = 0;
    material->texture_capacity = 1;

    material->flags = 0;
}

Material * material_new(void * shader) {
    Material * material = malloc(sizeof(Material));
    material_init(material, shader);
    return material;
}

void material_delete(Material * material) {
    if (material->flags & MATERIAL_FREE_TEXTURE) {
        for (int i = 0; i < material->texture_count; ++i) {
            texture_delete(*(material->textures + i));
        }
    }
    for (int i = 0; i < material->uniform_count; ++i) {
        uniform_deinit(material->uniforms + i);
    }
    free(material->textures);
    free(material->uniforms);
    free(material);
}

void material_prepare(Material * material) {
    shader_use(material->shader);
    for (int i = 0; i < material->texture_count; ++i) {
        texture_activate(*(material->textures + i), i);
    }
    for (int i = 0; i < material->uniform_count; ++i) {
        uniform_bind(material->uniforms + i);
    }
}

void material_add_uniform(Material * material, Uniform uniform) {
    // Resize the vector of uniforms if needed
    if (material->uniform_count >= material->uniform_capacity) {
        Uniform * re = realloc(material->uniforms, sizeof(Material) * material->uniform_count * 2);
        if (re == NULL) {
            free(material->uniforms);
            app_panic("Reallocation failure\n");
        } else {
            material->uniforms = re;
        }
        material->uniform_capacity *= 2;
    }

    // Add the uniform to the vector
    uniform_prepare(&uniform, material->shader);
    material->uniforms[material->uniform_count] = uniform;
    material->uniform_capacity++;
}

void material_add_texture(Material * material, Texture * texture) {
    // Resize the vector of texture pointers if needed.
    if (material->texture_count >= material->texture_capacity) {
        Texture ** re = realloc(material->textures, sizeof(Texture*) * material->texture_count * 2);
        if (re == NULL) {
            free(material->textures);
            app_panic("Reallocation failure\n");
        } else {
            material->textures = re;
        }
        material->texture_capacity *= 2;
    }

    // Add the texture to the vector.
    material->textures[material->texture_count] = texture;
    material->texture_count++;
}
