cmake_minimum_required(VERSION 3.27)
project(game_engine)

# Libraries
find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)
add_subdirectory(external/glad)

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
        kernel/visual/apis/opengl.c
        kernel/visual/apis/opengl.h
        kernel/visual/apis/graphics_api.h
        external/gl.h
        kernel/visual/apis/vulkan.c
        kernel/visual/apis/vulkan.h
        external/vulkan.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} external/glad ${VULKAN_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} glad vulkan)