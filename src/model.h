#pragma once
#include "mesh.h"


unsigned int model_init(struct mesh* msh);
void model_free(unsigned int mdl);
void model_bind(unsigned int mdl);
void model_draw(unsigned int mdl, int mode, int first, int count);
