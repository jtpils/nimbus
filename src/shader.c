#include "shader.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>


static const char* vs =
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "uniform mat4 mvp;\n"
    "void main() {\n"
    "    gl_Position = mvp * vec4(pos, 1.0);\n"
    "}\n";

static const char* fs =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\n";


unsigned int shader_init()
{
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int prog = glCreateProgram();

    glShaderSource(vert, 1, &vs, NULL);
    glShaderSource(frag, 1, &fs, NULL);
    glCompileShader(vert);
    glCompileShader(frag);
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glDeleteShader(vert);
    glDeleteShader(frag);

    return prog;
}


void shader_free(unsigned int shd)
{
}


void shader_args(unsigned int shd, int argc, struct uniform argv[])
{
    for (int i = 0; i < argc; ++i) {
        unsigned int loc = glGetUniformLocation(shd, argv[i].name);
        switch (argv[i].type) {
            case GL_MAT4:
                glUniformMatrix4fv(loc, 1, GL_FALSE, argv[i].data);
                break;
            default:
                break;
        }
    }
}


void shader_bind(unsigned int shd)
{
    glUseProgram(shd);
}
