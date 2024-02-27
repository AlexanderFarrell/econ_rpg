//
// Created by alexander on 2/27/24.
//

#ifndef ECON_RPG_FONT_H
#define ECON_RPG_FONT_H

#include <freetype/freetype.h>
//#include <ft2build.h>
//#include FT_FREETYPE_H
#include "texture.h"

#define GLYPH_COUNT 128
#define TEXTURE_SIZE_FONT 512

typedef struct Glyph Glyph;
struct Glyph {
    int x0, y0, x1, y1;
    float width, height, bearing;
    int bitmap_left, bitmap_top;
    int advance;
};

typedef struct Font Font;
struct Font {
    FT_Face face;
    int font_size;
    int max_size;
    Texture* texture;
    Glyph glyphs[GLYPH_COUNT];
};

Font* font_new(char * name, int font_size);
void font_delete(Font* font);
float font_get_width(Font* font, char * text);


#endif //ECON_RPG_FONT_H
