//
// Created by alexander on 2/26/24.
//

#include "shader.h"
#include "visual.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../fs/assets.h"

#define SHADER_MAX_LENGTH 100000

void * shader_from_files(char * filename) {
    unsigned long length = strlen(filename);

    char vert_path[length + 150];
    char frag_path[length + 150];

    char * asset_path = assets_get_content_path();

    sprintf(vert_path, "%s/content/visual/shader/%s.vert.glsl", asset_path, filename);
    sprintf(frag_path, "%s/content/visual/shader/%s.frag.glsl", asset_path, filename);

    free(asset_path);

    char * vert = assets_load_file_as_string(vert_path, SHADER_MAX_LENGTH);
    char * frag = assets_load_file_as_string(frag_path, SHADER_MAX_LENGTH);

    void * shader = shader_from_sources(vert, frag);

    free(vert);
    free(frag);

    return shader;
}

void * shader_from_sources(char * vert_source, char * frag_source) {
    return visual.graphics_api.shader_from_sources(vert_source, frag_source);
}

void shader_use(void * shader) {
    return visual.graphics_api.shader_use(shader);
}

void shader_delete(void * shader) {
    visual.graphics_api.shader_delete(shader);
}
