#pragma once
#include "mesh.h"


unsigned int model_init(struct mesh* msh);
void model_free(unsigned int mod);
void model_bind(unsigned int mod);
void model_draw(unsigned int mod, int mode, int first, int count);
