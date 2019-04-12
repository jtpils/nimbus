#pragma once


struct vertex {
    double x, y, z;
    double nx, ny, nz;
    unsigned char r, g, b;
};

struct pcd {
    struct vertex* data;
    int size;

    unsigned int vbo;
    unsigned int shd;
    unsigned int pip;
};

void pcd_load(struct pcd* pcd, const char* fname);
void pcd_save(struct pcd* pcd, const char* fname);
void pcd_alloc(struct pcd* pcd, int size);
void pcd_init(struct pcd* pcd);
void pcd_free(struct pcd* pcd);
void pcd_setup_gl(struct pcd* pcd);
