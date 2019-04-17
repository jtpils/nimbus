#include "glw.h"
#include <stdio.h>


unsigned int glw_buffer_init(struct buffer* buf)
{
    unsigned int id = 0;
    glGenBuffers(1, &id);
    glBindBuffer(buf->type, id);
    glBufferData(buf->type, buf->size, buf->data, buf->usage);
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


unsigned int glw_layout_init(struct layout* lay)
{
    unsigned int vao = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, lay->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lay->ebo);
    for (int i = 0; i < GLW_MAX_ATTRIBUTES; ++i) {
        struct attribute attr = lay->attrs[i];
        if (!attr.type) continue;
        glVertexAttribPointer(i, attr.size, attr.type, GL_FALSE, attr.stride, (void*)attr.offset);
        glEnableVertexAttribArray(i);
    }

    return vao;
}


void glw_shader_bind(unsigned int shd)
{
    glUseProgram(shd);
}


void glw_layout_bind(unsigned int lay)
{
    glBindVertexArray(lay);
}


void glw_buffer_free(unsigned int buf)
{
    glDeleteBuffers(1, &buf);
}


void glw_shader_free(unsigned int shd)
{
    glDeleteProgram(shd);
}


void glw_layout_free(unsigned int lay)
{
    glDeleteVertexArrays(1, &lay);
}


void glw_clear(int mask, vec4 color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(mask);
}


void glw_render(struct render* rnd)
{
    if (rnd->type == GLW_NONE) {
        glDrawArrays(rnd->mode, rnd->first, rnd->count);
    } else {
    }
}
