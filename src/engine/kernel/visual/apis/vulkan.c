//
// Created by alexander on 2/20/24.
//

#include "vulkan.h"
#include <stdlib.h>

void vulkan_init();
void vulkan_breakdown();
void vulkan_update();
void vulkan_update_late();

typedef struct VulkanContext VulkanContext;
struct VulkanContext {

};


GraphicsApi get_vulkan() {
    GraphicsApi graphics_api;

    graphics_api.context = NULL;
    graphics_api.init = vulkan_init;
    graphics_api.update = vulkan_update;
    graphics_api.update_late = vulkan_update_late;
    graphics_api.breakdown = vulkan_breakdown;

    return graphics_api;
}

void vulkan_init() {

}

void vulkan_breakdown() {

}

void vulkan_update() {

}

void vulkan_update_late() {

}
