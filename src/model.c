#include "model.h"
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>


unsigned int model_init(struct mesh* msh)
{
    unsigned int vao = 0;
    unsigned int vbo = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex) * msh->vc, msh->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    return vao;
}


void model_free(unsigned int mod)
{
}


void model_draw(unsigned int mod, int mode, int first, int count)
{
    glBindVertexArray(mod);
    glDrawArrays(mode, first, count);
}
