//
// Created by alexander on 2/27/24.
//

#include <stddef.h>
#include <stdlib.h>
#include "mesh.h"
#include "visual.h"
#include "../../util/swizzle.h"
#include "../../util/coords.h"

void vertex_attr_init(VertexAttr* attr, int elements_per_vertex, int count) {
    attr->elements_per_vertex = elements_per_vertex;
    size_t size = sizeof(float) * elements_per_vertex * count;
    attr->data = malloc(size);
}

void vertex_attr_deinit(VertexAttr* attr) {
    free(attr->data);
}

Mesh* mesh_new(VertexAttr* attrs, int* indices, int attr_count, int vertex_count, int index_count) {
    Mesh* mesh = malloc(visual.graphics_api.mesh_size);

    mesh->attr_count = attr_count;
    mesh->index_count = index_count;
    mesh->vertex_attrs = attrs;
    mesh->indices = indices;
    mesh->vertex_count = vertex_count;

    visual.graphics_api.mesh_init(mesh);

    return mesh;
}

Mesh* mesh_load_obj(char * filename) {
    return NULL;
}

void mesh_delete(Mesh* mesh) {
    visual.graphics_api.mesh_deinit(mesh);
}

void mesh_draw(Mesh* mesh) {
    visual.graphics_api.mesh_draw(mesh);
}

void mesh_debug(Mesh* mesh) {

}

void mesh_debug_specific(Mesh* mesh, uint8_t flags) {

}

static inline void mesh_create_cube_side(VertexAttr * buffers, int vertex_index_start,
                                         float x_start, float y_start, float z_start,
                                         float x_start1, float y_start1, float z_start1,
                                         float x_start2, float y_start2, float z_start2,
                                         float x_end, float y_end, float z_end,
                                         float x_normal, float y_normal, float z_normal);

Mesh* mesh_create_cube(float width, float height, float length) {
    int vertex_count = 24;
    VertexAttr * buffers = malloc(sizeof(VertexAttr) * 3);
    VertexAttr * positions = buffers;
    VertexAttr * uvs = buffers + 1;
    VertexAttr * normals = buffers + 2;

    vertex_attr_init(positions, 3, vertex_count);
    vertex_attr_init(uvs, 2, vertex_count);
    vertex_attr_init(normals, 3, vertex_count);

    mesh_create_cube_side(buffers, 0,
                          0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, length,
                          0.0f, height, 0.0f,
                          0.0f, height, length,
                          0.0f, 1.0f, 0.0f);
    mesh_create_cube_side(buffers, 4,
                          0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, length,
                          width, 0.0f, 0.0f,
                          width, 0.0f, length,
                          0.0f, 1.0f, 0.0f);
    mesh_create_cube_side(buffers, 20,
                          0.0f,  0.0f,   0.0f,
                          width,  0.0f,   0.0f,
                          0.0f,  height,   0.0f,
                          width, height, 0.0f,
                          0.0f, 1.0f, 0.0f);
    mesh_create_cube_side(buffers, 8,
                          width, 0.0f, 0.0f,
                          width, 0.0f, length,
                          width, height, 0.0f,
                          width, height, length,
                          0.0f, 1.0f, 0.0f);
    mesh_create_cube_side(buffers, 12,
                          0.0f, height, 0.0f,
                          width, height, 0.0f,
                          0.0f, height, length,
                          width, height, length,
                          0.0f, 1.0f, 0.0f);
    mesh_create_cube_side(buffers, 16,
                          0.0f,  0.0f, length,
                          width,  0.0f, length,
                          0.0f,  height, length,
                          width, height, length,
                          0.0f, 1.0f, 0.0f);
    int * indices = malloc(sizeof(int) * 6*6);
    set_xyz(indices+0,   0, 2, 1);
    set_xyz(indices+3,   1, 3, 2);
    set_xyz(indices+6,   4, 5, 6);
    set_xyz(indices+9,   5, 6, 7);
    set_xyz(indices+12,  8, 9, 10);
    set_xyz(indices+15,  9, 10, 11);

    set_xyz(indices+18, 12, 13, 14);
    set_xyz(indices+21, 13, 14, 15);
    set_xyz(indices+24, 16, 17, 18);
    set_xyz(indices+27, 17, 18, 19);
    set_xyz(indices+30, 20, 21, 22);
    set_xyz(indices+33, 21, 22, 23);

    return mesh_new(buffers, indices, 3, vertex_count, 36);
}

Mesh* mesh_create_plane(float width, float length) {
    int vertex_count = 4;
    VertexAttr * attrs = malloc(sizeof(VertexAttr) * 3);
    VertexAttr * positions = attrs;
    VertexAttr * uvs = attrs + 1;
    VertexAttr * normals = attrs + 2;

    vertex_attr_init(positions, 3, vertex_count);
    vertex_attr_init(uvs, 2, vertex_count);
    vertex_attr_init(normals, 3, vertex_count);
    set_xyz(attrs[0].data + 0, 0.0f, 0.0f, 0.0f);
    set_xyz(attrs[0].data + 3, 0.0f, 0.0f, length);
    set_xyz(attrs[0].data + 6, width, 0.0f, 0.0f);
    set_xyz(attrs[0].data + 9, width, 0.0f, length);
    set_xy(attrs[1].data + 0, 0.0f, 0.0f);
    set_xy(attrs[1].data + 2, 0.0f, 1.0f);
    set_xy(attrs[1].data + 4, 1.0f, 0.0f);
    set_xy(attrs[1].data + 6, 1.0f, 1.0f);
    set_xyz(attrs[2].data + 0, 0.0f, 1.0f, 0.0f);
    set_xyz(attrs[2].data + 3, 0.0f, 1.0f, 0.0f);
    set_xyz(attrs[2].data + 6, 0.0f, 1.0f, 0.0f);
    set_xyz(attrs[2].data + 9, 0.0f, 1.0f, 0.0f);

    int * indices = malloc(sizeof(int) * 6);
    set_xyz(indices, 0, 2, 1);
    set_xyz(indices+3, 1, 3, 2);
    return mesh_new(attrs, indices, 3, vertex_count, 6);
}

Mesh* mesh_create_sphere(float radius, int x_subdivisions, int y_subdivisions) {
    int vertex_count = (x_subdivisions) * (y_subdivisions) * 4;
    int index_count = (x_subdivisions) * (y_subdivisions) * 6;
    VertexAttr * buffers = malloc(sizeof(VertexAttr) * 3);
    VertexAttr * positions = &buffers[0];
    VertexAttr * uvs = &buffers[1];
    VertexAttr * normals = &buffers[2];
    vertex_attr_init(positions, 3, vertex_count);
    vertex_attr_init(uvs, 2, vertex_count);
    vertex_attr_init(normals, 3, vertex_count);

    int * indices = malloc(sizeof(int) * index_count);

    vec3 spherical = {radius, 0.0f, 0.0f};
    float y_dist = M_PI/(float)y_subdivisions;
    float x_dist = M_PI * 2/(float)x_subdivisions;
    int vertex_offset = 0;
    int index_offset  = 0;
    for (int y = 0; y < y_subdivisions; ++y) {
        for (int x = 0; x < x_subdivisions; ++x) {
            vec3 x1y0 = {spherical[0], spherical[1] + y_dist, spherical[2]};
            vec3 x0y1 = {spherical[0], spherical[1], spherical[2] + x_dist};
            vec3 x1y1 = {spherical[0], spherical[1] + y_dist, spherical[2] + x_dist};
            coords_spherical_to_cart(spherical, &positions->data[0 + (vertex_offset * 3)]);
            coords_spherical_to_cart(x1y0,      &positions->data[3 + (vertex_offset * 3)]);
            coords_spherical_to_cart(x0y1,      &positions->data[6 + (vertex_offset * 3)]);
            coords_spherical_to_cart(x1y1,      &positions->data[9 + (vertex_offset * 3)]);

            glm_normalize_to(&positions->data[0 + (vertex_offset * 3)], &normals->data[0 + (vertex_offset * 3)]);
            glm_normalize_to(&positions->data[3 + (vertex_offset * 3)], &normals->data[3 + (vertex_offset * 3)]);
            glm_normalize_to(&positions->data[6 + (vertex_offset * 3)], &normals->data[6 + (vertex_offset * 3)]);
            glm_normalize_to(&positions->data[9 + (vertex_offset * 3)], &normals->data[9 + (vertex_offset * 3)]);

            set_xy(&uvs->data[0 + (vertex_offset * 2)], (x + 0)/(float)x_subdivisions, (y + 0)/(float)y_subdivisions);
            set_xy(&uvs->data[2 + (vertex_offset * 2)], (x + 0)/(float)x_subdivisions, (y + 1)/(float)y_subdivisions);
            set_xy(&uvs->data[4 + (vertex_offset * 2)], (x + 1)/(float)x_subdivisions, (y + 0)/(float)y_subdivisions);
            set_xy(&uvs->data[6 + (vertex_offset * 2)], (x + 1)/(float)x_subdivisions, (y + 1)/(float)y_subdivisions);

            set_xyz(indices + 0 + index_offset, vertex_offset + 0, vertex_offset + 1, vertex_offset + 2);
            set_xyz(indices + 3 + index_offset, vertex_offset + 1, vertex_offset + 2, vertex_offset + 3);

            spherical[2] += x_dist;
            vertex_offset += 4;
            index_offset += 6;
        }
        spherical[1] += y_dist;
        spherical[2] = 0.0f;
    }
    Mesh * mesh = mesh_new(buffers, indices, 3, vertex_count, index_count);
//    mesh_debug_specific(mesh, MESH_DEBUG_VERTICES);
    return mesh;
}

static inline void mesh_create_cube_side(VertexAttr* buffers, int vertex_index_start,
                                         float x_start, float y_start, float z_start,
                                         float x_start1, float y_start1, float z_start1,
                                         float x_start2, float y_start2, float z_start2,
                                         float x_end, float y_end, float z_end,
                                         float x_normal, float y_normal, float z_normal) {
    set_xyz(buffers[0].data + (vertex_index_start + 0) * 3,  x_start,  y_start, z_start);
    set_xyz(buffers[0].data + (vertex_index_start + 1) * 3,  x_start1,  y_start1, z_start1);
    set_xyz(buffers[0].data + (vertex_index_start + 2) * 3,  x_start2, y_start2, z_start2);
    set_xyz(buffers[0].data + (vertex_index_start + 3) * 3,  x_end, y_end, z_end);
    set_xy (buffers[1].data + (vertex_index_start + 0) * 2,  0.0f, 0.0f);
    set_xy (buffers[1].data + (vertex_index_start + 1) * 2,  0.0f, 1.0f);
    set_xy (buffers[1].data + (vertex_index_start + 2) * 2,  1.0f, 0.0f);
    set_xy (buffers[1].data + (vertex_index_start + 3) * 2,  1.0f, 1.0f);
    set_xyz(buffers[2].data + (vertex_index_start + 0) * 3,  x_normal, y_normal, z_normal);
    set_xyz(buffers[2].data + (vertex_index_start + 1) * 3,  x_normal, y_normal, z_normal);
    set_xyz(buffers[2].data + (vertex_index_start + 2) * 3,  x_normal, y_normal, z_normal);
    set_xyz(buffers[2].data + (vertex_index_start + 3) * 3,  x_normal, y_normal, z_normal);
}