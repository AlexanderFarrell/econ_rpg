//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_APP_H
#define ECON_RPG_APP_H

#define STAGE_NAME_LENGTH 20
#define STAGE_NOT_FOUND 1

typedef struct Stage Stage;
struct Stage {
    char name[STAGE_NAME_LENGTH];
    void (*on_start)();
    void (*on_end)();
};

// Sets up the application
void app_setup(Stage * stages, int stage_count);

// Runs the application, given a stage to begin on.
void app_run(char * start_stage_name);

// Quits the application gracefully, performing proper breakdown steps.
void app_stop();

// Aborts the application immediately, skipping breakdown steps and prints an error.
void app_panic(char * format, ...) ;

// Switches to a different stage of the application given the string name of the stage.
int app_switch_stage(char * stage_name);


#endif //ECON_RPG_APP_H
