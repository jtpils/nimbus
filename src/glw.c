#include "glw.h"
#include <stdio.h>


unsigned int glw_buffer_init(struct buffer* buf)
{
    unsigned int id = 0;
    glGenBuffers(1, &id);
    glBindBuffer(id, buf->type);
    glBufferData(id, buf->size, buf->data, buf->usage);
    return id;
}


unsigned int glw_shader_init(struct shader* shd)
{
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int prog = glCreateProgram();

    glShaderSource(vert, 1, &(shd->vs.src), NULL);
    glShaderSource(frag, 1, &(shd->fs.src), NULL);
    glCompileShader(vert);
    glCompileShader(frag);
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glDeleteShader(vert);
    glDeleteShader(frag);

    return prog;
}


void glw_buffer_free(unsigned int buf)
{
    glDeleteBuffers(1, &buf);
}


void glw_shader_free(unsigned int shd)
{
    glDeleteProgram(shd);
}


void glw_pipeline_free(unsigned int pip)
{
    glDeleteVertexArrays(1, &pip);
}
