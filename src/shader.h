#pragma once


enum {
    GL_VEC2,
    GL_VEC3,
    GL_VEC4,
    GL_MAT4,
};

struct uniform {
    int type;
    const char* name;
    const void* data;
};

unsigned int shader_init();
void shader_free(unsigned int shd);
void shader_bind(unsigned int shd);
void shader_args(unsigned int shd, int argc, struct uniform argv[]);
