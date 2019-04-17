#pragma once
#include <stdbool.h>
#include "glw.h"
#include "camera.h"


struct app {
    void (*init_cb)(void);
    void (*draw_cb)(void);
    void (*cleanup_cb)(void);
    void (*error_cb)(void);

    int width;
    int height;
    int swap_interval;
    bool high_dpi;
    bool fullscreen;
    char* title;

    GLFWwindow* hwnd;
    struct camera cam;
};


int app_run(struct app* app);
