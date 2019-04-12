#pragma once
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#define GLW_MAX_UNIFORMS   16
#define GLW_MAX_ATTRIBUTES 8
#define GLW_NONE           0


typedef union {
    struct { float x, y, z; };
    struct { float r, g, b; };
} vec3;


typedef union {
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
} vec4;


struct buffer {
    int size;
    int type;
    int usage;
    void* data;
};

struct uniform {
    int type;
    const char* name;
};

struct args {
    int size;
    struct uniform uniforms[GLW_MAX_UNIFORMS];
};
b

struct stage {
    const char* src;
    struct args args;
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
    unsigned int shader;
    struct attribute attrs[GLW_MAX_ATTRIBUTES];
};

struct render {
    int primitive;
    int type;
    int first;
    int count;
};


unsigned int glw_buffer_init(struct buffer* buf);
unsigned int glw_shader_init(struct shader* shd);
unsigned int glw_layout_init(struct layout* lay);
void glw_layout_bind(unsigned int lay);
void glw_buffer_free(unsigned int buf);
void glw_shader_free(unsigned int shd);
void glw_layout_free(unsigned int pip);
void glw_clear(int mask, vec4 color);
void glw_render(struct render* rnd);
