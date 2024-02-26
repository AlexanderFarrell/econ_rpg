//
// Created by alexander on 2/24/24.
//

#include "camera.h"
#include "../../util/swizzle.h"

static void update_view(Camera* camera);
static void orthographic_update_projection(Camera* camera);
static void perspective_update_projection(Camera* camera);
static void camera_init(Camera* camera);
static void camera_orthographic_resize(Camera * camera, float width, float height);
static void camera_perspective_resize(Camera * camera, float width, float height);

void camera_orthographic_init(Orthographic * orthographic, float width, float height) {
    camera_init(&orthographic->camera);
    orthographic->left = 0.0f;
    orthographic->right = -width;
    orthographic->top = 0.0f;
    orthographic->bottom = height;
    orthographic->near_plane = 1.0f;
    orthographic->far_plane = 1000.0f;
    orthographic->camera.on_update = orthographic_update_projection;
    orthographic->camera.on_resize = camera_orthographic_resize;
    camera_update((Camera*)orthographic);
}

void camera_perspective_init(Perspective * perspective, float aspect_ratio) {
    camera_init(&perspective->camera);
    perspective->aspect_ratio = aspect_ratio;
    perspective->field_of_view = 85.0f;
    perspective->near_plane = 0.2f;
    perspective->far_plane = 500.0f;
    perspective->camera.on_update = perspective_update_projection;
    perspective->camera.on_resize = camera_perspective_resize;
    camera_update((Camera*)perspective);
}

void camera_orthographic_resize(Camera * camera, float width, float height) {
    Orthographic * orthographic = (Orthographic *) camera;
    orthographic->right = -width;
    orthographic->bottom = height;
}

void camera_perspective_resize(Camera * camera, float width, float height) {
    Perspective * perspective = (Perspective*) camera;
    float aspect_ratio = width/height;
    perspective->aspect_ratio = aspect_ratio;
}

void camera_update(Camera* camera) {
    update_view(camera);
    camera->on_update(camera);
    glm_mat4_mul(camera->projection_matrix, camera->view_matrix, camera->matrix);
}

// Private
static void camera_init(Camera* camera) {
    location_init(&camera->location);
    camera->location.position[2] = -1;
    location_refresh(&camera->location);
}

static void update_view(Camera* camera) {
    vec4 dir_unit;
    mat4 rot;
    vec4 dir;
    vec3 up;
    set_xyz(dir, 0.0f, 0.0f, 0.0f);
    set_xyzw(dir_unit, 0.0f, 0.0f, 1.0f, 1.0f);
    glm_quat_mat4(camera->location.rotation, rot);
    glm_mat4_mulv(rot, dir_unit, dir);
//    glm_vec3_add(dir, dir_unit, dir);
    glm_vec3_add(dir, camera->location.position, dir);
    set_xyz(up, 0.0f, 1.0f, 0.0f);
    glm_lookat_rh(camera->location.position, dir, up, camera->view_matrix);
}

static void orthographic_update_projection(Camera* camera) {
    Orthographic * ortho = (Orthographic*)camera;
    glm_ortho(ortho->left,
              ortho->right,
              ortho->bottom,
              ortho->top,
              ortho->near_plane,
              ortho->far_plane,
              ortho->camera.projection_matrix);
}

static void perspective_update_projection(Camera* camera) {
    Perspective * persp = (Perspective*)camera;
    glm_perspective(glm_rad(persp->field_of_view),
                    persp->aspect_ratio,
                    persp->near_plane,
                    persp->far_plane,
                    persp->camera.projection_matrix);
}
