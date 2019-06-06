#pragma once
#include "model.h"


struct render {
    unsigned int vao;
};


void render_init(struct render* rnd, struct model* mod);
