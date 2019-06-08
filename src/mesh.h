#pragma once
#include <cglm/cglm.h>


struct vertex {
    vec3 pos;
    vec3 normal;
    vec3 color;
};

struct mesh {
    int vc;
    int fc;
    int ec;
    ivec3* faces;
    struct vertex* vertices;
};

void mesh_load(struct mesh* msh, const char* fname);
void mesh_init(struct mesh* msh, int vc, int fc);
void mesh_free(struct mesh* msh);
