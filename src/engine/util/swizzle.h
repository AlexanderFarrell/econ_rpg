//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_SWIZZLE_H
#define ECON_RPG_SWIZZLE_H

#define set_xy(data, x, y) \
            *(data) = x;     \
            *(data + 1) = y;

#define set_xyz(data, x, y, z) \
            *(data) = x;     \
            *(data + 1) = y; \
            *(data + 2) = z;

#define set_xyzw(data, x, y, z, w) \
            *(data) = x;     \
            *(data + 1) = y; \
            *(data + 2) = z; \
            *(data + 3) = w;

#endif //ECON_RPG_SWIZZLE_H
