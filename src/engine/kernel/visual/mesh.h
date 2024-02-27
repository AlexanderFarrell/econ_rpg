//
// Created by alexander on 2/27/24.
//

#ifndef ECON_RPG_MESH_H
#define ECON_RPG_MESH_H

#include <stdint.h>

#define MESH_DEBUG_INDICES (1 << 0)
#define MESH_DEBUG_VERTICES (1 << 1)
#define MESH_DEBUG_POINTERS (1 << 2)
#define MESH_DEBUG_VAO (1 << 3)

typedef struct VertexAttr VertexAttr;
struct VertexAttr {
    int elements_per_vertex;
    float * data;
};

typedef struct Mesh Mesh;
struct Mesh {
    VertexAttr * vertex_attrs;
    int * indices;
    int attr_count;
    int vertex_count;
    int index_count;
};

void vertex_attr_init(VertexAttr* attr, int elements_per_vertex, int count);
void vertex_attr_deinit(VertexAttr* attr);

Mesh* mesh_new(VertexAttr* attrs,
               int* indices,
               int attr_count,
               int vertex_count,
               int index_count);
Mesh* mesh_load_obj(char * filename);
void mesh_delete(Mesh* mesh);
void mesh_draw(Mesh* mesh);

void mesh_debug(Mesh* mesh);
void mesh_debug_specific(Mesh* mesh, uint8_t flags);

Mesh* mesh_create_cube(float width, float height, float length);
Mesh* mesh_create_plane(float width, float length);
Mesh* mesh_create_sphere(float radius, int x_subdivisions, int y_subdivisions);

#endif //ECON_RPG_MESH_H
