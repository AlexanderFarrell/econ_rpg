//
// Created by alexander on 2/26/24.
//

#include "gl_uniform.h"
#include "../../external/gl.h"
#include "gl_shader.h"
#include <stdlib.h>

typedef void (*GlUniformBinding)(GLint location, GLsizei count, const GLfloat *value);

static void uniform_4fv_binding(GLint location, GLsizei count, const GLfloat *value) {
    glUniform4fv(location, count, value);
}

static void uniform_3fv_binding(GLint location, GLsizei count, const GLfloat *value) {
    glUniform3fv(location, count, value);
}

static void uniform_2fv_binding(GLint location, GLsizei count, const GLfloat *value) {
    glUniform2fv(location, count, value);
}

static void uniform_1fv_binding(GLint location, GLsizei count, const GLfloat *value) {
    glUniform1fv(location, count, value);
}

const GlUniformBinding uniform_bindings[] = {
    uniform_4fv_binding,
    uniform_3fv_binding,
    uniform_2fv_binding,
    uniform_1fv_binding
};

typedef struct GLUniformData GLUniformData;
struct GLUniformData {
    GLint location;
};

void gl_uniform_prepare(Uniform* uniform, void * shader) {
    GLUniformData * data = malloc(sizeof(GLUniformData));
    GLShader * gl_shader = shader;
    data->location = glGetUniformLocation(gl_shader->program, uniform->name);
    uniform->binding_data = data;
}

void gl_uniform_bind(Uniform * uniform) {
    GLUniformData * data = uniform->binding_data;
    if (uniform->kind == UK_Matrix4x4) {
        glUniformMatrix4fv(data->location,
                           1,
                           0,
                           uniform->data);
    } else {
        uniform_bindings[uniform->kind](data->location, 1, uniform->data);
    }
}
