//
// Created by alexander on 2/24/24.
//

#include "assets.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../console/console.h"
#include "../../core/app.h"
#if __APPLE__
#include <mach-o/dyld.h>
#include <libgen.h>
#include <unistd.h>
#elif __linux
#include <unistd.h>
#endif
#define PATH_MAX 1016

char * assets_load_file_as_string(char * filename, int size_limit){
//    printf("Loading File: %s\n",filename );
    char *buffer = NULL;
    long length;
    FILE *file = fopen(filename, "rb");

    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = (char*)malloc(length + 1);
        if (buffer) {
            fread(buffer, 1, length, file);
            fclose(file);
            buffer[length] = '\0';
            return buffer;
        } else {
            log_error("Cannot load file, out of memory.\n");
            fclose(file);
            return NULL;
        }
    } else {
        log_error("Failed to load file as string: %s\n", filename);
        return NULL;
    }
}

char * assets_load_file_content_as_string(char * relative_path, int size_limit) {
    char * asset_path = assets_get_content_path();
    char path[1024];
    sprintf(path, "%s/%s", asset_path, relative_path);
    free(asset_path);
    return assets_load_file_as_string(path, size_limit);
}

char * assets_get_content_path() {
    char path[PATH_MAX];
#if __APPLE__
    uint32_t path_length = sizeof(path);
    int err = _NSGetExecutablePath(path, &path_length);
    if (err) {
        printf("ERROR: Cannot get asset content path");
        exit(1);
    }
    chdir(dirname(path));
    for (int i = strnlen(path, path_length); i >= 0; --i) {
        if (path[i] == '/') {
            path[i] = '\0';
            break;
        }
    }
    uint32_t path_length_true = strnlen(path, PATH_MAX);
    char * ret_val = malloc(path_length_true + 2);
    strncpy(ret_val, path, path_length_true + 1);
    return ret_val;
#else
    if (getcwd(path, PATH_MAX) != NULL) {
        size_t size = strnlen(path, PATH_MAX);
        char * ret_val = malloc(size + 2);
        strncpy(ret_val, path, size + 1);
        return ret_val;
    } else {
        app_panic("Error getting current directory.");
        return NULL;
    }
//    printf("ERROR: Cannot get asset content path. UNKNOWN PLATFORM");
//    exit(1);
////    return "/";
#endif
}