#pragma once
#include <stdbool.h>
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "control.h"


struct app {
    float aspect;
    int width;
    int height;
    int swap_interval;
    char* title;
    bool high_dpi;
    bool fullscreen;
    bool redraw;
    GLFWwindow* hwnd;
};


int app_run(struct app* app);
