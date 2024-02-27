//
// Created by alexander on 2/26/24.
//

#include "uniform.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "visual.h"

void uniform_init(Uniform* uniform, char * name, UniformKind kind) {
    int size;
    switch (kind) {
        case UK_Vector4:
            size = 1;
            break;
        case UK_Vector3:
            size = 3;
            break;
        case UK_Vector2:
            size = 2;
            break;
        case UK_Scaler:
            size = 1;
            break;
        case UK_Matrix4x4:
            size = 16;
            break;
    }
    uniform->kind = kind;
    uniform->data = (float*) malloc(sizeof(float) * size);
    uint64_t i = strnlen(name, 1000) + 1;
    uniform->name = (char*) malloc(i + 2);
    strncpy(uniform->name, name, i + 1);
    uniform->binding_data = NULL;
}

void uniform_deinit(Uniform* uniform) {
    free(uniform->data);
    free(uniform->name);
    if (uniform->binding_data != NULL) {
        free(uniform->binding_data);
    }
}

void uniform_prepare(Uniform* uniform, void * shader) {
    visual.graphics_api.uniform_prepare(uniform, shader);
}

void uniform_bind(Uniform* uniform) {
    visual.graphics_api.uniform_bind(uniform);
}
