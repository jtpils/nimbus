#pragma once
#include <cglm/cglm.h>


struct model {
    int   size;
    vec3* points;
    vec3* normals;
    vec3* colors;
};

void model_load(struct model* mod, const char* fname);
