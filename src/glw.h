#pragma once
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#define MAX_UNIFORMS 16


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
    struct uniform uniforms[MAX_UNIFORMS];
};

struct stage {
    const char* src;
    struct args args;
};

struct shader {
    struct stage vs; /* vertex shader */
    struct stage fs; /* fragment shader */
};

struct pipeline {
    unsigned int shader;
};


unsigned int glw_buffer_init(struct buffer* buf);
unsigned int glw_shader_init(struct shader* shd);
unsigned int glw_pipeline_init(struct pipeline* pip);
void glw_buffer_free(unsigned int buf);
void glw_shader_free(unsigned int shd);
void glw_pipeline_free(unsigned int pip);
