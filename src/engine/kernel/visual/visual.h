//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_VISUAL_H
#define ECON_RPG_VISUAL_H

#include "graphics_api.h"

typedef struct Visual Visual;
struct Visual {
    float clear_color[3];
    GraphicsApi graphics_api;
};

extern Visual visual;

void visual_start(char * graphics_api);
void visual_update();
void visual_update_late();
void visual_end();

#endif //ECON_RPG_VISUAL_H
