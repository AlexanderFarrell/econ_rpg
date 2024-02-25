//
// Created by alexander on 2/24/24.
//
#include <base.h>
#include <engine.h>
#include "menu/menu.h"

int main() {
    Stage stages[] = {
        menu_stage
    };

    app_setup(stages, 1);
    app_run("Menu");
}