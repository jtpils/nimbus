#include "pcd.h"
#include <string.h>
#include <stdlib.h>
#include "ply.h"


static void pcd_vertex_cb(double v, const char* name, int i, void* data)
{
    struct pcd* pcd = (struct pcd*)(data);
    if (!strcmp(name, "x")) pcd->data[i].pos[0] = v;
    else if (!strcmp(name, "y")) pcd->data[i].pos[1] = v;
    else if (!strcmp(name, "z")) pcd->data[i].pos[2] = v;
    else if (!strcmp(name, "red")) pcd->data[i].color[0] = v / 255.0;
    else if (!strcmp(name, "green")) pcd->data[i].color[1] = v / 255.0;
    else if (!strcmp(name, "blue")) pcd->data[i].color[2] = v / 255.0;
    else if (!strcmp(name, "nx")) pcd->data[i].normal[0] = v;
    else if (!strcmp(name, "ny")) pcd->data[i].normal[1] = v;
    else if (!strcmp(name, "nz")) pcd->data[i].normal[2] = v;
}


void pcd_load(struct pcd* pcd, const char* fname)
{
    struct ply* pp = ply_init();

    FILE* fp = fopen(fname, "rb");
    ply_init_io(pp, fp);
    ply_read_header(pp);

    int size = ply_element_count(pp, "vertex");
    pcd_alloc(pcd, size);
    ply_set_read_cb(pp, "vertex", pcd_vertex_cb, pcd);
    ply_read(pp);

    ply_free(pp);
    fclose(fp);
}


void pcd_alloc(struct pcd* pcd, int size)
{
    pcd->data = realloc(pcd->data,  sizeof(struct vertex) * size);
    pcd->size = size;
}


void pcd_free(struct pcd* pcd)
{
    free(pcd->data);
    pcd->size = 0;
    pcd->data = NULL;
}
