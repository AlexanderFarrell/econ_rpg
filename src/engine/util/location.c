//
// Created by alexander on 2/24/24.
//

#include "location.h"
#include "swizzle.h"
#include <cglm/cglm.h>

void location_init(Location* location) {
    set_xyz(location->position, 0.0f, 0.0f, 0.0f);
    set_xyz(location->scale, 1.0f, 1.0f, 1.0f);
    set_xyzw(location->rotation, 0.0f, 0.0f, 0.0f, 1.0f);
}

Location * location_new() {
    Location * location = malloc(sizeof(Location));
    location_init(location);
    return location;
}

void location_refresh(Location* location) {
    mat4 rotation_matrix;
    glm_mat4_identity(location->matrix);
    glm_translate(location->matrix, location->position);
    glm_quat_mat4(location->rotation, rotation_matrix);
    glm_mat4_mul(location->matrix, rotation_matrix, location->matrix);
    glm_scale(location->matrix, location->scale);
}

// Rectangle
void location_rect_init(Location* location, float x, float y, float width, float height) {
    location_set_x(location,x);
    location_set_y(location,y);
    location_set_width(location,width);
    location_set_height(location,height);
    location_refresh(location);
}

void location_rect_init_size(Location* location, float width, float height) {
    location_set_x(location,0);
    location_set_y(location,0);
    location_set_width(location,width);
    location_set_height(location,height);
}

void location_anchor_left(Location* location, float x) {
    location_set_x(location, x);
}

void location_anchor_right(Location* location, float x) {
    location_set_x(location, x - location_width(location));
}

void location_anchor_top(Location* location, float y) {
    location_set_y(location, y);
}

void location_anchor_bottom(Location* location, float y) {
    location_set_y(location, y - location_height(location));
}

void location_anchor_center_x(Location* location, float x_start, float x_end) {
    float mid_parent = (x_end - x_start) / 2 + x_start;
    float mid_self = location_width(location)/2;
    location_set_x(location, mid_parent - mid_self);
}

void location_anchor_center_y(Location* location, float y_start, float y_end) {
    float mid_parent = (y_end - y_start) / 2 + y_start;
    float mid_self = location_height(location)/2;
    location_set_y(location, mid_parent - mid_self);
}

void location_set_depth(Location* location, float depth) {
    location->position[2] = depth;
}

void location_set_rectangle(Location* location, float x, float y, float width, float height) {
    location_set_x(location,x);
    location_set_y(location,y);
    location_set_width(location,width);
    location_set_height(location,height);
}

void location_display(Location* location) {
    location_display_specific(location, LOCATION_DISPLAY_PRS | LOCATION_DISPLAY_MATRIX);
}

void location_display_specific(Location* location, int flags) {
    if (flags & LOCATION_DISPLAY_PRS) {
        printf(" --- Location ---\n");
        printf("Position: %f %f %f\n", location->position[0], location->position[1], location->position[2]);
        printf("Rotation: %f %f %f %f\n", location->rotation[0], location->rotation[1], location->rotation[2], location->rotation[3]);
        printf("Scale:    %f %f %f\n", location->scale[0], location->scale[1], location->scale[2]);
    }
    if (flags & LOCATION_DISPLAY_MATRIX) {
        printf(" ---  Matrix  ---\n");
        mat4_display(location->matrix);
    }
}

extern inline float location_x(Location* location);
extern inline float location_y(Location* location);
extern inline float location_width(Location* location);
extern inline float location_height(Location* location);
extern inline void location_set_x(Location* location, float x);
extern inline void location_set_y(Location* location, float y);
extern inline void location_set_width(Location* location, float width);
extern inline void location_set_height(Location* location, float height);
extern inline void mat4_display(mat4 matrix);
extern inline void location_scale_xy(Location* location, float amo);
