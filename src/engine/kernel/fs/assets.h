//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_ASSETS_H
#define ECON_RPG_ASSETS_H

char * assets_get_content_path();
char * assets_load_file_as_string(char * filename, int size_limit);
char * assets_load_file_content_as_string(char * relative_path, int size_limit);

#endif //ECON_RPG_ASSETS_H
