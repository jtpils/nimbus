#pragma once
#include <stdbool.h>
#include "glw.h"
#include "camera.h"


enum {
    APP_KEY_DOWN,
    APP_MOUSE_DOWN,
    APP_MOUSE_SCROLL,
};

struct event {
    int type;
    int key;
    int mods;
    int mouse;
    float move[2];
    float scroll[2];
};

struct app {
    void (*init_cb)(void);
    void (*draw_cb)(void);
    void (*cleanup_cb)(void);
    void (*error_cb)(void);
    void (*event_cb)(struct event*);

    int width;
    int height;
    int swap_interval;
    bool high_dpi;
    bool fullscreen;
    char* title;

    GLFWwindow* hwnd;
};


int app_run(struct app* app);
