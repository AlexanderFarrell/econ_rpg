//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_TEXTURE_H
#define ECON_RPG_TEXTURE_H

#include <stdint.h>
#include "cglm/vec3.h"

#define TEXTURE_HAS_ALPHA (1 << 0)
#define TEXTURE_GEN_MIPMAP (1 << 1)

typedef enum TextureFormat TextureFormat;
enum TextureFormat {
    TF_RGBA_8,
    TF_RGB_8,
    TF_GRAYSCALE_8
};

typedef enum TextureFilter TextureFilter;
enum TextureFilter {
    Nearest,
    NearestMipmap,
    Bilinear,
    Trilinear
};

typedef struct Texture Texture;
struct Texture {
    uint16_t width;
    uint16_t height;
    TextureFormat format;
    TextureFilter filter;
    uint8_t * data;
    uint8_t flags;
};

// --- Texture Initialization ---

// Initializes a given texture with a width, height and given flags.
void texture_init(Texture * texture, uint16_t width, uint16_t height, uint8_t flags);

// Heap allocates memory for a new texture, and calls texture_init
Texture * texture_new(uint16_t width, uint16_t height, uint8_t flags);

// Heap allocates a new texture from a PNG. Calls texture_buffer for you.
Texture * texture_load_png(char * filename);

// Heap allocates a new texture from a color. Calls texture_buffer for you.
Texture * texture_from_color(vec3 color);

// Heap allocates a new texture from a gradient where the first color is on the left,
// and the second color is on the right. Calls texture_buffer for you.
Texture * texture_from_gradient_x(vec3 left, vec3 right, int width, int height);

// Heap allocates a new texture from a gradient where the first color is on the top,
// and the second color is on the bottom. Calls texture_buffer for you.
Texture * texture_from_gradient_y(vec3 top, vec3 bottom, int width, int height);

// -- Texture Use --

// Updates the memory on the GPU with the current set memory on the CPU. Must call this
// to see changes apply to the texture from the CPU.
void texture_buffer(Texture * texture);

// Tells the GPU to use this texture when drawing. Multiple textures can be set, with
// the index of each one being set as n. To use one texture, set n to 0.
void texture_activate(Texture * texture, int n);

// -- Texture Destroy --

// Breaks down a texture on the GPU and any internal heap allocated memory.
void texture_deinit(Texture * texture);

// Calls deinit and frees the texture if heap allocated. Only call if
// this texture was created using a heap allocating initializer.
void texture_delete(Texture * texture);


#endif //ECON_RPG_TEXTURE_H
