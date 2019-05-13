#pragma once
#include "type.h"


struct pcd {
    int size;
    struct vertex* data;
};


void pcd_load(struct pcd* pcd, const char* fname);
void pcd_save(struct pcd* pcd, const char* fname);
void pcd_alloc(struct pcd* pcd, int size);
void pcd_free(struct pcd* pcd);
