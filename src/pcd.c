#include "pcd.h"
#include <string.h>
#include <stdlib.h>
#include "glw.h"
#include "ply.h"


static void vertex_cb(double v, const char* name, int i, void* data)
{
    struct pcd* pcd = (struct pcd*)(data);
    if (!strcmp(name, "x")) pcd->data[i].x = v;
    else if (!strcmp(name, "y")) pcd->data[i].y = v;
    else if (!strcmp(name, "z")) pcd->data[i].z = v;
    else if (!strcmp(name, "red")) pcd->data[i].r = v;
    else if (!strcmp(name, "green")) pcd->data[i].g = v;
    else if (!strcmp(name, "blue")) pcd->data[i].b = v;
    else if (!strcmp(name, "nx")) pcd->data[i].nx = v;
    else if (!strcmp(name, "ny")) pcd->data[i].ny = v;
    else if (!strcmp(name, "nz")) pcd->data[i].nz = v;
}


void pcd_setup_gl(struct pcd* pcd)
{
    struct buffer vbo = {
        .size = pcd->size * sizeof(struct vertex),
        .type = GL_ARRAY_BUFFER,
        .usage = GL_STATIC_DRAW,
        .data = pcd->data
    };
    struct shader shd = {
        .vs.src =
        "#version 330\n"
        "in vec3 pos;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 1.0);\n"
        "}\n",
        .fs.src =
        "#version 330\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}\n"
    };

    pcd->vbo = glw_buffer_init(&vbo);
    pcd->shd = glw_shader_init(&shd);
}


void pcd_load(struct pcd* pcd, const char* fname)
{
    FILE* fp = fopen(fname, "rb");
    struct ply* pp = ply_init();
    ply_init_io(pp, fp);
    ply_read_header(pp);

    int size = ply_element_count(pp, "vertex");
    pcd_alloc(pcd, size);

    ply_set_read_cb(pp, "vertex", vertex_cb, pcd);
    ply_read(pp);

    ply_free(pp);
    fclose(fp);
}


void pcd_alloc(struct pcd* pcd, int size)
{
    pcd->data = realloc(pcd->data, sizeof(struct vertex) * size);
    pcd->size = size;
}


void pcd_free(struct pcd* pcd)
{
    pcd->size = 0;
    free(pcd->data);
    glw_buffer_free(pcd->vbo);
    glw_shader_free(pcd->shd);
    glw_pipeline_free(pcd->pip);
}
