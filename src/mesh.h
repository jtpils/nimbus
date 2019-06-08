#pragma once
#include <cglm/cglm.h>


struct vertex {
    vec3 pos;
    vec3 normal;
    vec3 color;
};

struct mesh {
    int vc, ec, fc;
    struct vertex* vertices;
    ivec3* faces;
};

void mesh_load(struct mesh* msh, const char* fname);
void mesh_alloc(struct mesh* msh, int vc, int fc);