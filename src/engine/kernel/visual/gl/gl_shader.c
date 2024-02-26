//
// Created by alexander on 2/26/24.
//

#include "gl_shader.h"
#include <stdlib.h>
#include "../../console/console.h"

static GLuint shader_compile(char * source, GLenum type);
static GLuint shader_create_program_vf(char * vert_source, char * frag_source);

void * gl_shader_from_sources(char * vert_source, char * frag_source) {
    GLShader * shader = malloc(sizeof(GLShader));
    shader->program = shader_create_program_vf(vert_source, frag_source);
    return (void*)shader;
}

void gl_shader_delete(void * shader) {
    GLShader * gl_shader = shader;
    glDeleteProgram(gl_shader->program);
    free(shader);
}

void gl_shader_use(void * shader) {
    GLShader * gl_shader = shader;
    glUseProgram(gl_shader->program);
}

static GLuint shader_compile(char * source, GLenum type) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, (const GLchar *const *)&source, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *buffer = (char *) malloc(length);
        glGetShaderInfoLog(shader,
                           length,
                           NULL,
                           buffer);
        log_error("ERROR: Error when compiling shader\n - %s\n", buffer);
        exit(1);
    }

    return shader;
}

static GLuint shader_create_program_vf(char * vert_source, char * frag_source) {
    GLuint vert_shader = shader_compile(vert_source, GL_VERTEX_SHADER);
    GLuint frag_shader = shader_compile(frag_source, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *buffer = (char *) malloc(length);
        glGetProgramInfoLog(program,
                            length,
                            NULL,
                            buffer);
        log_error("ERROR: Error when linking shader program\n - %s\n", buffer);
        exit(1);
    }
    glDetachShader(program, vert_shader);
    glDetachShader(program, frag_shader);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    return program;
}