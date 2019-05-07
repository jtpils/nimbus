#pragma once
#include "glw.h"


struct vertex {
    vec3 pos;
    vec3 normal;
    vec3 color;
};

struct pcd {
    int size;
    struct vertex* data;

    mat4 mvp;

    unsigned int vbo;
    unsigned int shd;
    unsigned int lay;
};

void pcd_load(struct pcd* pcd, const char* fname);
void pcd_save(struct pcd* pcd, const char* fname);
void pcd_alloc(struct pcd* pcd, int size);
void pcd_init(struct pcd* pcd);
void pcd_free(struct pcd* pcd);
void pcd_setup_gl(struct pcd* pcd);
void pcd_draw(struct pcd* pcd);
void pcd_centroid(struct pcd* pcd, vec3 centroid);
