cmake_minimum_required(VERSION 3.27)
project(game_engine)

# Libraries
find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)
add_subdirectory(external/glad)
add_subdirectory(external/cglm)
add_subdirectory(external/spng)

add_library(${PROJECT_NAME} engine.h engine.c
        core/app.c
        core/app.h
        core/config.c
        core/config.h
        kernel/console/console.c
        kernel/console/console.h
        kernel/fs/assets.c
        kernel/fs/assets.h
        kernel/kernel.c
        kernel/kernel.h
        kernel/input/input.c
        kernel/input/input.h
        kernel/visual/visual.c
        kernel/visual/visual.h
        kernel/window/window.c
        kernel/window/window.h
        util/error.h
        kernel/visual/gl/opengl.c
        kernel/visual/gl/opengl.h
        kernel/visual/graphics_api.h
        external/gl.h
        kernel/visual/vulkan/vulkan.c
        kernel/visual/vulkan/vulkan.h
        external/vulkan.h
        kernel/visual/camera.c
        kernel/visual/camera.h
        util/location.c
        util/location.h
        util/swizzle.h
        kernel/visual/shader.c
        kernel/visual/shader.h
        kernel/visual/gl/gl_shader.c
        kernel/visual/gl/gl_shader.h
        kernel/visual/uniform.c
        kernel/visual/uniform.h
        kernel/visual/gl/gl_uniform.c
        kernel/visual/gl/gl_uniform.h
        kernel/visual/texture.c
        kernel/visual/texture.h
        kernel/visual/gl/gl_texture.c
        kernel/visual/gl/gl_texture.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS}
        external/glad ${VULKAN_INCLUDE_DIRS} external/cglm external/spng)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} glad vulkan cglm spng)