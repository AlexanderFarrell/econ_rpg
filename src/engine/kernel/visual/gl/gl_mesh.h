//
// Created by alexander on 2/27/24.
//

#ifndef ECON_RPG_GL_MESH_H
#define ECON_RPG_GL_MESH_H

#include "../mesh.h"

int gl_mesh_size();
void gl_mesh_init(Mesh* mesh);
void gl_mesh_deinit(Mesh* mesh);
void gl_mesh_draw(Mesh* mesh);

#endif //ECON_RPG_GL_MESH_H
