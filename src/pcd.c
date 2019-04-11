#include "pcd.h"
#include <string.h>
#include <stdlib.h>
#include "glw.h"
#include "ply.h"


static void vertex_cb(double v, const char* name, int i, void* data)
{
    struct pcd* pcd = (struct pcd*)(data);
    if (!strcmp(name, "x")) pcd->pos[i].x = v;
    else if (!strcmp(name, "y")) pcd->pos[i].y = v;
    else if (!strcmp(name, "z")) pcd->pos[i].z = v;
    else if (!strcmp(name, "red")) pcd->color[i].r = v;
    else if (!strcmp(name, "green")) pcd->color[i].g = v;
    else if (!strcmp(name, "blue")) pcd->color[i].b = v;
    else if (!strcmp(name, "nx")) pcd->normal[i].x = v;
    else if (!strcmp(name, "ny")) pcd->normal[i].y = v;
    else if (!strcmp(name, "nz")) pcd->normal[i].z = v;
}


void pcd_setup_gl(struct pcd* pcd)
{
    struct buffer vbo = {
        .size = pcd->size * sizeof(vec3),
        .type = GL_ARRAY_BUFFER,
        .usage = GL_STATIC_DRAW,
        .data = pcd->pos
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
    pcd->pos = realloc(pcd->pos, sizeof(vec3) * size);
    pcd->normal = realloc(pcd->normal, sizeof(vec3) * size);
    pcd->color = realloc(pcd->color, sizeof(vec3) * size);
    pcd->size = size;
}


void pcd_free(struct pcd* pcd)
{
    pcd->size = 0;
    free(pcd->pos);
    free(pcd->normal);
    free(pcd->color);

    glw_buffer_free(pcd->vbo);
    glw_shader_free(pcd->shd);
    glw_pipeline_free(pcd->pip);
}
