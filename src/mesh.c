#include "mesh.h"
#include <stdio.h>
#include <string.h>
#include "ply.h"


static void vertex_cb(double v, const char* name, int i, void* data)
{
    struct mesh* msh = (struct mesh*)(data);
    if (!strcmp(name, "x")) msh->vertices[i].pos[0] = v;
    else if (!strcmp(name, "y")) msh->vertices[i].pos[1] = v;
    else if (!strcmp(name, "z")) msh->vertices[i].pos[2] = v;
    else if (!strcmp(name, "red")) msh->vertices[i].color[0] = v / 255.0;
    else if (!strcmp(name, "green")) msh->vertices[i].color[1] = v / 255.0;
    else if (!strcmp(name, "blue")) msh->vertices[i].color[2] = v / 255.0;
    else if (!strcmp(name, "nx")) msh->vertices[i].normal[0] = v;
    else if (!strcmp(name, "ny")) msh->vertices[i].normal[1] = v;
    else if (!strcmp(name, "nz")) msh->vertices[i].normal[2] = v;
}


void mesh_load(struct mesh* msh, const char* fname)
{
    FILE* fp = fopen(fname, "rb");
    struct ply* pp = ply_init();
    ply_init_io(pp, fp);
    ply_read_header(pp);

    int V = ply_element_count(pp, "vertex");
    int F = ply_element_count(pp, "face");
    mesh_alloc(msh, V, F);

    ply_set_read_cb(pp, "vertex", vertex_cb, msh);
    ply_read(pp);

    ply_free(pp);
    fclose(fp);
}


void mesh_alloc(struct mesh* msh, int V, int F)
{
    msh->V = V;
    msh->F = F;
    msh->vertices = realloc(msh->vertices, sizeof(struct vertex) * V);
}
