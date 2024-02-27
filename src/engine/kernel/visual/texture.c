//
// Created by alexander on 2/26/24.
//

#include "texture.h"
#include <spng/spng.h>
#include "../fs/assets.h"
#include "visual.h"
#include "../console/console.h"

static Texture * texture_load_png_internal(char * filename);

void texture_init(Texture * texture, uint16_t width, uint16_t height, uint8_t flags) {
    texture->width = width;
    texture->height = height;
    texture->flags = flags;
    texture->filter= Bilinear;
    if (texture->flags & TEXTURE_HAS_ALPHA) {
        texture->format = TF_RGBA_8;
        texture->data = malloc(sizeof(uint8_t) * width * height * 4);
    } else {
        texture->format = TF_RGB_8;
        texture->data = malloc(sizeof(uint8_t) * width * height * 3);
    }
}

Texture * texture_new(uint16_t width, uint16_t height, uint8_t flags) {
    Texture * texture = malloc(visual.graphics_api.texture_size);
    texture_init(texture, width, height, flags);
    return texture;
}

Texture * texture_load_png(char * filename) {
    Texture * texture = texture_load_png_internal(filename);
    texture_buffer(texture);
    return texture;
}

Texture * texture_from_color(vec3 color) {

}

Texture * texture_from_gradient_x(vec3 left, vec3 right, int width, int height) {

}

Texture * texture_from_gradient_y(vec3 top, vec3 bottom, int width, int height) {

}

void texture_buffer(Texture * texture) {
    visual.graphics_api.texture_buffer(texture);
}

void texture_activate(Texture * texture, int n) {
    visual.graphics_api.texture_activate(texture, n);
}

void texture_deinit(Texture * texture) {
    visual.graphics_api.texture_destroy(texture);
}

void texture_delete(Texture * texture) {
    free(texture);
}

static Texture * texture_load_png_internal(char * filename) {
    char * asset_path = assets_get_content_path();
    char path[1024];
    sprintf(path, "%s/content/visual/textures/%s", asset_path, filename);
    free(asset_path);

    spng_ctx *png_ctx = spng_ctx_new(0);
    FILE *png_file = fopen(path, "rb");

    if (png_file == NULL) {
        log_warn("TEXTURE LOAD FAILURE: Could not open file: %s \n", path);
        return NULL;
    }

    spng_set_png_file(png_ctx, png_file);
    struct spng_ihdr ihdr = {0};

    int ihdr_error = spng_get_ihdr(png_ctx, &ihdr);
    if (ihdr_error) {
        const char * error = spng_strerror(ihdr_error);
        log_error("%s\n", error);
        exit(1);
    }

    int has_alpha = ihdr.color_type == SPNG_COLOR_TYPE_GRAYSCALE_ALPHA ||
                    ihdr.color_type == SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;

    size_t image_size;
    int decoded_size_error;
    enum spng_format format = (has_alpha) ? SPNG_FMT_RGBA8 : SPNG_FMT_RGB8;

    decoded_size_error = spng_decoded_image_size(png_ctx, format, &image_size);
    if (decoded_size_error) {
        const char * error = spng_strerror(ihdr_error);
        log_error("%s\n", error);
        exit(1);
    }

    Texture* texture = texture_new(ihdr.width,
                                   ihdr.height,
                                   TEXTURE_HAS_ALPHA | TEXTURE_GEN_MIPMAP);

    spng_decode_image(png_ctx, texture->data, image_size, format, 0);
    spng_ctx_free(png_ctx);
    log_verbose("Loaded texture %s successfully\n", filename);
    return texture;
}