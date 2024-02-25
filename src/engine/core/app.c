//
// Created by alexander on 2/24/24.
//

#include "app.h"
#include "../kernel/console/console.h"
#include "../kernel/fs/assets.h"
#include "../kernel/kernel.h"
#include "../util/error.h"
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include <signal.h>



#define APP_RUNNING (1 << 0)
#define APP_SHOULD_SWITCH_STAGE (1 << 1)
#define APP_IS_SETUP (1 << 2)

typedef struct App App;
struct App {
    Stage * stages;
    Stage * current;
    Stage * future;
    int stage_count;
    char flags;
};

App app = {0};

void app_switch_stage_internal();
void app_handle_signal(int signo);

void app_setup(Stage * stages, int stage_count) {
    app.stages = stages;
    app.stage_count = stage_count;
    app.future = NULL;
    app.current = NULL;
    app.flags = APP_IS_SETUP;
}

void app_run(char * start_stage_name) {
    if (!(app.flags & APP_IS_SETUP)) {
        app_panic("App has not properly set up. Please call app_setup()\n");
    }

    if (signal(SIGINT, app_handle_signal) == SIG_ERR) {
        log_warn("Signal handler failed to set up for Interrupt Signal\n");
    }

    if (signal(SIGTERM, app_handle_signal) == SIG_ERR) {
        log_warn("Signal handler failed to set up for Terminate Signal\n");
    }

    if (signal(SIGQUIT, app_handle_signal) == SIG_ERR) {
        log_warn("Signal handler failed to set up for Terminate Signal\n");
    }

    // Start Up Stage
    app.flags |= APP_RUNNING;
    config_load_default();
    log_info("Starting %s\n", config_get_str("name"));
    kernel_start();
//    spirit_start();
//    world_start();

    //Stage Initialization
    if (app_switch_stage(start_stage_name) != OK) {
        app_panic("App failed to start with stage \"%s\". Not found.\n", start_stage_name);
    }
    app_switch_stage_internal();

    while (app.flags & APP_RUNNING) {
        kernel_update();
//        spirit_update();
//        world_update();

        if (app.flags & APP_SHOULD_SWITCH_STAGE) {
            app_switch_stage_internal();
        }
    }

    //Stage Breakdown
    if (app.current->on_end != NULL) {
        app.current->on_end();
    }

    log_info("Closing %s\n", config_get_str("name"));
//    world_end();
//    spirit_end();
    kernel_end();
}

void app_stop() {
    app.flags &= ~APP_RUNNING;
}

void app_panic(char * format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[Error] ");
    vfprintf(stderr, format, args);
    va_end(args);
    abort();
}

int app_switch_stage(char * stage_name) {
    for (int i = 0; i < app.stage_count; ++i) {
        if (strncmp(stage_name, app.stages[i].name, STAGE_NAME_LENGTH) == 0) {
            app.flags |= APP_SHOULD_SWITCH_STAGE;
            app.future = &app.stages[i];
            return OK;
        }
    }

    return STAGE_NOT_FOUND;
}

void app_switch_stage_internal() {
    if (app.current != NULL && app.current->on_end != NULL) {
        app.current->on_end();
    }

    app.current = app.future;
    app.future = NULL;

    if (app.current->on_start != NULL) {
        app.current->on_start();
    }

    app.flags &= ~ APP_SHOULD_SWITCH_STAGE;
}

void app_handle_signal(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        app_stop();
    }

    if (signo == SIGQUIT) {
        app_panic("Shutting down immediately as requested\n");
    }
}