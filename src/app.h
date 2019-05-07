#pragma once
#include <stdbool.h>
#include "glw.h"
#include "camera.h"


enum {
    APP_KEY_DOWN,
    APP_KEY_UP,
    APP_MOUSE_CURSOR,
    APP_MOUSE_DOWN,
    APP_MOUSE_UP,
    APP_MOUSE_SCROLL,
};

struct event {
    int type;
    int key;
    int mods;
    int mouse;
    float pos[2];
    float scroll[2];
};

struct app {
    void (*init_cb)();
    void (*draw_cb)();
    void (*cleanup_cb)();
    void (*error_cb)();
    void (*event_cb)(struct event*);

    int width;
    int height;
    int swap_interval;
    bool high_dpi;
    bool fullscreen;
    char* title;

    GLFWwindow* hwnd;
};


int   app_run(struct app* app);
float app_get_time();
