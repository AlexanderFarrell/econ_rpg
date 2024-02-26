//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_CAMERA_H
#define ECON_RPG_CAMERA_H

#include "../../util/location.h"

typedef struct Camera Camera;
struct Camera {
    void (*on_update)(Camera* camera);
    void (*on_resize)(Camera* camera, float width, float height);
    Location location;
    mat4 matrix;
    mat4 view_matrix;
    mat4 projection_matrix;
};

typedef struct Orthographic Orthographic ;
struct Orthographic {
    Camera camera;
    float left;
    float right;
    float top;
    float bottom;
    float near_plane;
    float far_plane;
};

typedef struct Perspective Perspective;
struct Perspective {
    Camera camera;
    float aspect_ratio;
    float field_of_view;
    float near_plane;
    float far_plane;
};

void camera_orthographic_init(Orthographic* orthographic, float width, float height);
void camera_perspective_init(Perspective* perspective, float aspect_ratio);
void camera_update(Camera* camera);

#endif //ECON_RPG_CAMERA_H
