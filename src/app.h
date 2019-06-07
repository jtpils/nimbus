#pragma once
#include <stdbool.h>
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "mesh.h"


struct app {
    int width;
    int height;
    char* title;
};

int app_run(struct app* app);
void app_model_push(struct app* app, struct mesh* msh);
void app_model_pop(struct app* app);
