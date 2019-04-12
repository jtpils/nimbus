#include "pcd.h"
#include <string.h>
#include <stdlib.h>
#include "glw.h"
#include "ply.h"


static void vertex_cb(double v, const char* name, int i, void* data)
{
    struct pcd* pcd = (struct pcd*)(data);
    if (!strcmp(name, "x")) pcd->data[i].pos.x = v;
    else if (!strcmp(name, "y")) pcd->data[i].pos.y = v;
    else if (!strcmp(name, "z")) pcd->data[i].pos.z = v;
    else if (!strcmp(name, "red")) pcd->data[i].color.r = v / 255.0;
    else if (!strcmp(name, "green")) pcd->data[i].color.g = v / 255.0;
    else if (!strcmp(name, "blue")) pcd->data[i].color.b = v / 255.0;
    else if (!strcmp(name, "nx")) pcd->data[i].normal.x = v;
    else if (!strcmp(name, "ny")) pcd->data[i].normal.y = v;
    else if (!strcmp(name, "nz")) pcd->data[i].normal.z = v;
}


void pcd_setup_gl(struct pcd* pcd)
{
    struct buffer vbo = {
        .size = pcd->size * sizeof(struct vertex),
        .type = GL_ARRAY_BUFFER,
        .usage = GL_STATIC_DRAW,
        .data = pcd->data
    };
    pcd->vbo = glw_buffer_init(&vbo);

    struct shader shd = {
        .vs.src =
        "#version 330\n"
        "layout (location = 0) in vec3 pos;\n"
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
    pcd->shd = glw_shader_init(&shd);

    struct layout lay = {
        .vbo = pcd->vbo,
        .attrs = {
            [0] = {
                .size = 3,
                .type = GL_FLOAT,
                .stride = sizeof(struct vertex),
                .offset = 0
            },
        }
    };
    pcd->lay = glw_layout_init(&lay);
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
    glw_layout_free(pcd->lay);
}


void pcd_draw(struct pcd* pcd)
{
    struct render rnd = {
        .mode = GL_POINTS,
        .type = GLW_NONE,
        .first = 0,
        .count = pcd->size
    };
    glw_shader_bind(pcd->shd);
    glw_layout_bind(pcd->lay);
    glw_render(&rnd);
}
