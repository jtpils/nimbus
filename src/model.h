#pragma once
#include "mesh.h"


struct model {
    unsigned int vao;
};

void model_new(struct model* mod, struct mesh* msh);
void model_del(struct model* mod);
