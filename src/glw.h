#pragma once
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define GLW_MAX_ATTRIBUTES 8
#define GLW_NONE           0


enum {
    GLW_FLOAT,
    GLW_FLOAT2,
    GLW_FLOAT3,
    GLW_FLOAT4,
    GLW_MAT4
};

struct buffer {
    int size;
    int type;
    int usage;
    void* data;
};

struct uniform {
    int type;
    const char* name;
    const void* data;
};

struct stage {
    const char* src;
};

struct shader {
    struct stage vs; /* vertex shader */
    struct stage fs; /* fragment shader */
};

struct attribute {
    int size;
    int type;
    int stride;
    size_t offset;
};

struct layout {
    unsigned int vbo;
    unsigned int ebo;
    struct attribute attrs[GLW_MAX_ATTRIBUTES];
};

struct render {
    int mode;
    int type;
    int first;
    int count;
};


unsigned int glw_buffer_init(struct buffer* buf);
unsigned int glw_shader_init(struct shader* shd);
unsigned int glw_layout_init(struct layout* lay);
void glw_shader_bind(unsigned int shd);
void glw_shader_args(unsigned int shd, struct uniform* args, int n);
void glw_layout_bind(unsigned int lay);
void glw_buffer_free(unsigned int buf);
void glw_shader_free(unsigned int shd);
void glw_layout_free(unsigned int pip);
void glw_clear(int mask, vec4 color);
void glw_render(struct render* rnd);
