//
// Created by alexander on 2/24/24.
//

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../kernel/console/console.h"
#include "../kernel/fs/assets.h"


// ---- Types ----
typedef struct ConfigItem ConfigItem;
struct ConfigItem {
    char * key;
    char * value;
};

// ---- Variables ----
#define MAX_CONTENT_FILE_SIZE 100000
#define DEFAULT_CONFIG_PATH "config.cfg"
static ConfigItem * config_items;
static int size;
static int capacity;

// ---- Functions ----
static void config_add_item(char * key, char * value);

void config_load(char * filename){
    config_items = malloc(sizeof(ConfigItem));
    size = 0;
    capacity = 1;
    char * contents = assets_load_file_content_as_string(filename, MAX_CONTENT_FILE_SIZE);
    if (contents == NULL) {
        log_error("Failed to load config file\n");
        return;
    }
    int contents_length = (int)strnlen(contents, MAX_CONTENT_FILE_SIZE) + 1;
    int cursor = 0;

    int key_start = 0;
    int value_start = 0;
    int skip_line = 0;
    int has_pair = 0;
    int line = 0;
    while (cursor < contents_length) {
        if (contents[cursor] == '=') {
            cursor++;
            value_start = cursor;
            has_pair = 1;
        } else if (contents[cursor] == '\n' || contents[cursor] == '\0' || contents[cursor] == '\377') {
            cursor++;
            if (!skip_line && has_pair) {
                int key_length = value_start - key_start - 1;
                int value_length = cursor - value_start - 1;
                if (key_length > 0 && value_length > 0) {
                    char * key = malloc(sizeof(key_length));
                    char * value = malloc(sizeof(value_length));
                    strncpy(key, contents + key_start, key_length);
                    strncpy(value, contents + value_start, value_length);

                    key[key_length] = '\0';
                    value[value_length] = '\0';
                    config_add_item(key, value);
                } else {
                    if (key_length == 0) {
                        printf("%sWarning: Missing key in config on line %d \n%s", C_YELLOW, line, C_RESET);
                    }
                    if (value_length == 0) {
                        printf("%sWarning: Missing value in config on line %d \n%s", C_YELLOW, line, C_RESET);
                    }
                }
            }
            key_start = cursor;
            skip_line = 0;
            has_pair = 0;
            line++;
        } else if (contents[cursor] == ';') {
            skip_line = 1;
            cursor++;
        } else {
            cursor++;
        }
    }

    free(contents);
}

void config_load_default(){
    config_load(DEFAULT_CONFIG_PATH);
}

void config_unload(){
    free(config_items);
    size = 0;
    capacity = 0;
}

char * config_get_str(char * key){
    for (int i = 0; i < size; i++) {
        if (strcmp(config_items[i].key, key) == 0) {
            return config_items[i].value;
        }
    }
    log_error("Key not found\n");
    return NULL;
}

int config_get_int(char * key){
    char * value_str = config_get_str(key);
    if (value_str == NULL) {
        log_error("Key not found, cannot convert NULL to int %s\n", key);
        exit(1);
    }
    return atoi(value_str);
}

float config_get_float(char * key){
    char * value_str = config_get_str(key);
    if (value_str == NULL) {
        log_error("Key not found, cannot convert NULL to float %s\n", key);
        exit(1);
    }
    return atof(value_str);
}

static void config_add_item(char * key, char * value) {
    if (capacity <= size) {
        capacity *= 2;
        config_items = realloc(config_items, sizeof(ConfigItem) * capacity);
    }
    config_items[size].key = key;
    config_items[size].value = value;
    size++;
}

const char * config_default_contents = "; The name of the game application. Will display on the window.\n"
                                       "name=Buried Peace\n"
                                       "\n"
                                       "; The publisher of the application\n"
                                       "publisher=Alexander Farrell\n"
                                       "\n"
                                       "; The major product version\n"
                                       "major_version=0\n"
                                       "\n"
                                       "; The minor revision version\n"
                                       "minor_version=1\n"
                                       "\n"
                                       "; The size, from left and right, of the =window in pixels. Recommended value 1280\n"
                                       "window_width=1440\n"
                                       "\n"
                                       "; The size, from top to bottom, of the window in pixels. Recommended value 720\n"
                                       "window_height=900";