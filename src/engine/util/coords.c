//
// Created by alexander on 2/27/24.
//

#include "coords.h"


void coords_cart_to_polar(vec2 cart, vec2 dest) {
    dest[0] = sqrtf(cart[0] * cart[0] + cart[1] * cart[1]); // Radius
    dest[1] = atan2f(cart[1], cart[0]); // Azimuth
}

void coords_polar_to_cart(vec2 polar, vec2 dest) {
    dest[0] = polar[0] * cosf(polar[1]); // X
    dest[1] = polar[0] * sinf(polar[1]); // Y
}

void coords_cart_to_cylindrical(vec3 cart, vec3 dest) {
    dest[0] = sqrtf(cart[0] * cart[0] + cart[2] * cart[2]); // Radius
    dest[1] = cart[1]; // Height
    dest[2] = atan2f(cart[2], cart[0]); // Azimuth
}

void coords_cylindrical_to_cart(vec3 cylindrical, vec3 dest) {
    dest[0] = cylindrical[0] * cosf(cylindrical[2]); // X
    dest[1] = cylindrical[1];
    dest[2] = cylindrical[0] * sinf(cylindrical[2]); // Z
}

void coords_cart_to_spherical(vec3 cart, vec3 dest) {
//    float optimized = sqrtf(cart[0] * cart[0] + cart[1] * cart[1]);
    dest[0] = sqrtf(cart[0] * cart[0] + cart[1] * cart[1] + cart[2] * cart[2]);
    dest[2] = acosf(cart[2] / (dest[0]));
    dest[1] = atan2f(cart[2], cart[0]); // Azimuth
}

void coords_spherical_to_cart(vec3 spherical, vec3 dest) {
    dest[0] = spherical[0] * sinf(spherical[1]) * cosf(spherical[2]);
    dest[2] = spherical[0] * sinf(spherical[1]) * sinf(spherical[2]);
    dest[1] = spherical[0] * cosf(spherical[1]);





//    dest[2] = spherical[0] * sinf(spherical[2]); // Y
}
