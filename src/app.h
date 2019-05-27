#pragma once
#include <stdbool.h>
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


struct event {
    int type;
};

struct app {
    int width;
    int height;
    char* title;

    void (*init_cb)(void);
    void (*draw_cb)(void);
    void (*close_cb)(void);
    void (*event_cb)(struct event*);
};


int app_run(struct app* app);
