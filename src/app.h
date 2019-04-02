#pragma once
#include <stdbool.h>
#include <GLFW/glfw3.h>


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
    const char* title;

    GLFWwindow* hwnd;
};


int app_run(struct app* app);
