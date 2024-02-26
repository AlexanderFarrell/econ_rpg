//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_GL_SHADER_H
#define ECON_RPG_GL_SHADER_H

#include "../../external/gl.h"

typedef struct GLShader GLShader;
struct GLShader {
    GLuint program;
};

void * gl_shader_from_sources(char * vert_source, char * frag_source);
void gl_shader_use(void * shader) ;
void gl_shader_delete(void * shader);

#endif //ECON_RPG_GL_SHADER_H
