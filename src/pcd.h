#pragma once


typedef struct { double x, y, z; } vec3;
typedef struct { unsigned char r, g, b; } rgb8;

struct pcd {
    vec3* position;
    vec3* normal;
    rgb8* color;
    int size;

    int vao;
    int vbo;
    int ebo;
};

void pcd_load(struct pcd* pcd, const char* fname);
void pcd_save(struct pcd* pcd, const char* fname);
