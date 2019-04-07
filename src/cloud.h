#pragma once


typedef struct { double x, y, z; } vec3;
typedef struct { unsigned char r, g, b; } rgb8;

struct cloud {
    vec3* position;
    vec3* normal;
    rgb8* color;
    int size;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

void cloud_load(struct cloud* pcd, const char* fname);
void cloud_save(struct cloud* pcd, const char* fname);
