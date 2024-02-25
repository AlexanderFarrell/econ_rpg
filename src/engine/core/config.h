//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_CONFIG_H
#define ECON_RPG_CONFIG_H

// --- Config Loading and Unloading ---

// Loads the config given a filename
void config_load(char * filename);

// Loads the config given CONFIG_DEFAULT_FILENAME
void config_load_default();

// Clears the config data.
void config_unload();


// --- Retrieves Values from the Config

// Get the value as a string
char * config_get_str(char * key);

// Get the value as an integer
int config_get_int(char * key);

// Get the value as a float
float config_get_float(char * key);

//void config_set_str(char * key, char * value);
//void config_set_int(char * key, int value);
//void config_set_float(char * key, float value);

#endif //ECON_RPG_CONFIG_H
