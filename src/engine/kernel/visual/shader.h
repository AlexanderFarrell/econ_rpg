//
// Created by alexander on 2/26/24.
//

#ifndef ECON_RPG_SHADER_H
#define ECON_RPG_SHADER_H

void * shader_from_files(char * filename);
void * shader_from_sources(char * vert_source, char * frag_source);
void shader_use(void * shader);
void shader_delete(void * shader);

#endif //ECON_RPG_SHADER_H
