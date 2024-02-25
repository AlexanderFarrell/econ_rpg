//
// Created by alexander on 2/20/24.
//

#ifndef ECONOMICS_SIMULATOR_GL_H
#define ECONOMICS_SIMULATOR_GL_H

#if __APPLE__
#define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl3.h>
#elif __linux__
#include <include/glad/glad.h>
#elif _WIN32
#include <windows.h>
    #include <GL/gl.h>
#endif

#endif //ECONOMICS_SIMULATOR_GL_H
