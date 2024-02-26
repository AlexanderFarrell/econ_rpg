//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_GL_UNIFORM_H
#define ECON_RPG_GL_UNIFORM_H
#include "../uniform.h"

void gl_uniform_prepare(Uniform* uniform, void * shader);
void gl_uniform_bind(Uniform * uniform);

#endif //ECON_RPG_GL_UNIFORM_H
