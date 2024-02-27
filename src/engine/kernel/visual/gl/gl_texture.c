//
// Created by alexander on 2/26/24.
//

#include "gl_texture.h"

static int texture_bindings[] = {
    GL_TEXTURE0,
    GL_TEXTURE1,
    GL_TEXTURE2,
    GL_TEXTURE3,
    GL_TEXTURE4,
    GL_TEXTURE5,
    GL_TEXTURE6,
    GL_TEXTURE7,
    GL_TEXTURE8,
    GL_TEXTURE9,
    GL_TEXTURE10
};

void gl_texture_buffer(Texture* texture) {
    GLTexture * gl_texture = (GLTexture*)texture;
    glDeleteBuffers(1, &gl_texture->binding);
    glGenBuffers(1, &gl_texture->binding);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    switch (gl_texture->texture.filter) {
        case Nearest:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case NearestMipmap:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case Bilinear:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case Trilinear:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }
    GLint format;
    switch (gl_texture->texture.format) {
        case TF_RGBA_8:
            format = GL_RGBA;
            break;
        case TF_RGB_8:
            format = GL_RGB;
            break;
        case TF_GRAYSCALE_8:
            format = GL_RED;
            break;
    }

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        (GLint)texture->width,
        (GLint)texture->height,
        0,
        format,
        format,
        texture->data);
    if (texture->flags & TEXTURE_GEN_MIPMAP) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void gl_texture_activate(Texture* texture, int n) {
    GLTexture * gl_texture = (GLTexture*)texture;
    glActiveTexture(texture_bindings[n]);
    glBindTexture(GL_TEXTURE_2D, gl_texture->binding);
}

void gl_texture_destroy(Texture* texture) {
    GLTexture * gl_texture = (GLTexture*)texture;
    glDeleteBuffers(1, &gl_texture->binding);
}
