//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_LOCATION_H
#define ECON_RPG_LOCATION_H

#include <cglm/cglm.h>

#define LOCATION_DISPLAY_PRS (1 << 0)
#define LOCATION_DISPLAY_MATRIX (1 << 1)

typedef struct Location Location;
struct Location {
    vec3 position;
    vec4 rotation;
    vec3 scale;
    mat4 matrix;
};

void location_init(Location* location);
Location * location_new();
void location_refresh(Location* location);

// Rectangle Transforms
void location_rect_init(Location* location, float x, float y, float width, float height);
void location_rect_init_size(Location* location, float width, float height);
void location_anchor_left(Location* location, float x);
void location_anchor_right(Location* location, float x);
void location_anchor_top(Location* location, float y);
void location_anchor_bottom(Location* location, float y);
void location_anchor_center_x(Location* location, float x_start, float x_end);
void location_anchor_center_y(Location* location, float y_start, float y_end);
void location_set_depth(Location* location, float depth);
void location_set_rectangle(Location* location, float x, float y, float width, float height);

inline float location_x(Location* location) {
    return location->position[0];
}

inline float location_y(Location* location) {
    return location->position[1];
}

inline float location_width(Location* location) {
    return location->scale[0];
}

inline float location_height(Location* location) {
    return location->scale[1];
}

inline void location_set_x(Location* location, float x) {
    location->position[0] = x;
}

inline void location_set_y(Location* location, float y) {
    location->position[1] = y;
}

inline void location_set_width(Location* location, float width) {
    location->scale[0] = width;
}

inline void location_set_height(Location* location, float height) {
    location->scale[1] = height;
}

inline void location_scale_xy(Location* location, float amo) {
    location->scale[0] *= amo;
    location->scale[1] *= amo;
}

void location_display(Location* location);
void location_display_specific(Location* location, int flags);

inline void mat4_display(mat4 matrix) {
    printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
           matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
           matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
           matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
           matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
}

#endif //ECON_RPG_LOCATION_H
