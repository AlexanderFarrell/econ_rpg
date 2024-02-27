//
// Created by alexander on 2/20/24.
//

#include "opengl.h"
#include <SDL2/SDL.h>
#include "../graphics_api.h"
#include "../../window/window.h"
#include "../visual.h"
#include "../../../external/gl.h"
#include "gl_uniform.h"
#include "gl_shader.h"
#include "gl_texture.h"


#define GL_MAJOR_VERSION_DEFAULT 3
#define GL_MINOR_VERSION_DEFAULT 3
#define GL_PROFILE_DEFAULT SDL_GL_CONTEXT_PROFILE_CORE

void opengl_init();
void opengl_breakdown();
void opengl_update();
void opengl_update_late();

GraphicsApi get_opengl() {
    GraphicsApi graphics_api;

    graphics_api.init = opengl_init;
    graphics_api.breakdown = opengl_breakdown;
    graphics_api.update = opengl_update;
    graphics_api.update_late = opengl_update_late;
    graphics_api.shader_from_sources = gl_shader_from_sources;
    graphics_api.shader_use = gl_shader_use;
    graphics_api.shader_delete = gl_shader_delete;
    graphics_api.uniform_prepare = gl_uniform_prepare;
    graphics_api.uniform_bind = gl_uniform_bind;
    graphics_api.texture_size = sizeof(GLTexture);
    graphics_api.texture_activate = gl_texture_activate;
    graphics_api.texture_destroy = gl_texture_destroy;
    graphics_api.texture_buffer = gl_texture_buffer;

    return graphics_api;
}

void opengl_init() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VERSION_DEFAULT);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VERSION_DEFAULT);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, GL_PROFILE_DEFAULT);

    SDL_GLContext * context = SDL_GL_CreateContext(window.sdl_window);
    visual.graphics_api.context = context;

    SDL_GL_LoadLibrary(NULL);

#if __linux__
    gladLoadGLLoader(SDL_GL_GetProcAddress);
#elif __APPLE__

#elif __MINGW32__ // Windows

#endif

}

void opengl_breakdown() {
    SDL_GLContext * context = visual.graphics_api.context;



    SDL_GL_DeleteContext(context);
}

void opengl_update() {
    glViewport(0, 0, window.width, window.height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(visual.clear_color[0],
                 visual.clear_color[1],
                 visual.clear_color[2],
                 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
}

void opengl_update_late() {
    glFlush();
    SDL_GL_SwapWindow(window.sdl_window);
}
