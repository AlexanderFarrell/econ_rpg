//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_UNIFORM_H
#define ECON_RPG_UNIFORM_H

typedef enum UniformKind UniformKind;
enum UniformKind {
    UK_Vector4 = 0,
    UK_Vector3 = 1,
    UK_Vector2 = 2,
    UK_Scaler = 3,
    UK_Matrix4x4 = 4
};

typedef struct Uniform Uniform;
struct Uniform {
    char * name;
    float * data;
    UniformKind kind;
    void * binding_data;
};

void uniform_init(Uniform* uniform, char * name, UniformKind kind);
void uniform_prepare(Uniform* uniform, void * shader);
void uniform_deinit(Uniform* uniform);
void uniform_bind(Uniform* uniform);

#endif //ECON_RPG_UNIFORM_H
