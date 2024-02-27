//
// Created by alexander on 2/26/24.
//

#include "play.h"

void play_on_start();
void play_on_end();

const Stage play_stage = {
    .name = "Play",
    .on_start = play_on_start,
    .on_end = play_on_end,
};

void play_on_start() {

}

void play_on_end() {

}
