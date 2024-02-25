//
// Created by alexander on 2/24/24.
//
#include <base.h>
#include <engine.h>
#include <kernel/window/window.h>

void editor_on_start();
void editor_on_end();

Stage editor_stage = {
    .name = "Editor",
    .on_start = editor_on_start,
    .on_end = editor_on_end,
};

int main() {
    app_setup(&editor_stage, 1);
    app_run("Editor");
}

void editor_on_start() {
    window_set_title("ERPG Editor");
}

void editor_on_end() {

}
