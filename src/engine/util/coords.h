//
// Created by alexander on 2/27/24.
//

#ifndef ECON_RPG_COORDS_H
#define ECON_RPG_COORDS_H

#include "cglm/cglm.h"

// Conversions
void coords_cart_to_polar(vec2 cart, vec2 dest);
void coords_polar_to_cart(vec2 polar, vec2 dest);
void coords_cart_to_cylindrical(vec3 cart, vec3 dest);
void coords_cylindrical_to_cart(vec3 cylindrical, vec3 dest);
void coords_cart_to_spherical(vec3 cart, vec3 dest);
void coords_spherical_to_cart(vec3 spherical, vec3 dest);

// Barycentric

// Getters

// Setters

#endif //ECON_RPG_COORDS_H
