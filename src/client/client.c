//
// Created by alexander on 2/24/24.
//

#include <engine.h>
#include "menu/menu.h"
#include "play/play.h"

int main() {
    Stage stages[] = {
        menu_stage,
        play_stage
    };

    app_setup(stages, 2);
    app_run("Menu");
}