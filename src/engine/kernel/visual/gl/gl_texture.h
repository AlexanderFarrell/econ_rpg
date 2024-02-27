//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_GL_TEXTURE_H
#define ECON_RPG_GL_TEXTURE_H

#include "../texture.h"
#include "../../external/gl.h"

typedef struct GLTexture GLTexture;
struct GLTexture {
    Texture texture;
    GLuint binding;
};

void gl_texture_buffer(Texture* texture);
void gl_texture_activate(Texture* texture, int n);
void gl_texture_destroy(Texture* texture);

#endif //ECON_RPG_GL_TEXTURE_H
