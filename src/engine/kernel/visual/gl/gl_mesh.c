//
// Created by alexander on 2/27/24.
//

#include <stdlib.h>
#include "gl_mesh.h"
#include "include/glad/glad.h"

typedef struct GLMesh GLMesh;
struct GLMesh {
    Mesh mesh;
    GLuint index_buffer;
    GLuint * vertex_buffers;
    GLuint vao;
};

static void gl_buffer_create(Mesh* mesh, VertexAttr* attr) {

}

int gl_mesh_size() {
    return sizeof(GLMesh);
}

void gl_mesh_init(Mesh* mesh) {
    GLMesh * gl_mesh = (GLMesh*)mesh;
    gl_mesh->vertex_buffers = malloc(sizeof(GLuint) * mesh->attr_count);
    for (int i = 0; i < mesh->attr_count; ++i) {
        glGenBuffers(1, &gl_mesh->vertex_buffers[i]);
        glBindBuffer(GL_ARRAY_BUFFER, gl_mesh->vertex_buffers[i]);
        glBufferData(GL_ARRAY_BUFFER,
                     (GLsizeiptr) (mesh->vertex_count * mesh->vertex_attrs[i].elements_per_vertex * sizeof(float)),
                     mesh->vertex_attrs[i].data,
                     GL_STATIC_DRAW);
    }

    glGenVertexArrays(1, &gl_mesh->vao);
    glBindVertexArray(gl_mesh->vao);

    // Colors, Texture, Normal, Positions, etc.
    for (int i = 0; i < mesh->attr_count; ++i) {
        glEnableVertexAttribArray(i);
        glBindBuffer(GL_ARRAY_BUFFER,
                     gl_mesh->vertex_buffers[i]);
        glVertexAttribPointer(i,
                              mesh->vertex_attrs[i].elements_per_vertex,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              NULL);
    }

    glGenBuffers(1, &gl_mesh->index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_mesh->index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 (GLsizeiptr) (mesh->index_count * sizeof(int)),
                 mesh->indices,
                 GL_STATIC_DRAW);
}

void gl_mesh_deinit(Mesh* mesh) {
    GLMesh* gl_mesh = (GLMesh*)mesh;
    glDeleteBuffers(1, &gl_mesh->index_buffer);
    for (int i = 0; i < mesh->attr_count; ++i) {
        glDeleteBuffers(1, &gl_mesh->vertex_buffers[i]);
    }

    free(gl_mesh->vertex_buffers);
}

void gl_mesh_draw(Mesh* mesh) {
    GLMesh* gl_mesh = (GLMesh*)mesh;
    glBindVertexArray(gl_mesh->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_mesh->index_buffer);
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, (void *) 0);

//    GLint a_size = 0;
//    GLint b_size = 0;
//    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &a_size);
//    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &b_size);
}