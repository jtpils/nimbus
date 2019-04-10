#pragma once


typedef struct { double x, y, z; } vec3;
typedef struct { unsigned char r, g, b; } rgb8;

struct pcd {
    vec3* pos;
    vec3* normal;
    rgb8* color;
    int size;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

void pcd_load(struct pcd* pcd, const char* fname);
void pcd_save(struct pcd* pcd, const char* fname);
void pcd_alloc(struct pcd* pcd, int size);
void pcd_init(struct pcd* pcd);
void pcd_free(struct pcd* pcd);
