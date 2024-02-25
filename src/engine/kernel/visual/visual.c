//
// Created by alexander on 2/24/24.
//

#include "visual.h"
#include <string.h>
#include "apis/opengl.h"
#include "../console/console.h"
#include "../../core/app.h"


Visual visual;

void visual_start(char * graphics_api_name) {
    visual.clear_color[0] = 0.5f;
    visual.clear_color[1] = 0.6f;
    visual.clear_color[2] = 0.8f;
    if (strncmp(graphics_api_name, "opengl", 20) == 0) {
        visual.graphics_api = get_opengl();
        log_info("Starting OpenGL!\n");
    } else {
        app_panic("Unsupported graphics API %s\n", graphics_api_name);
    }

    visual.graphics_api.init();
}

void visual_update() {
    visual.graphics_api.update();
}

void visual_update_late() {
    visual.graphics_api.update_late();
}

void visual_end() {
    visual.graphics_api.breakdown();
}
