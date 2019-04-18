#include "app.h"
#include <stdio.h>

#define APP_EVENT_STACK_SIZE 16


struct state {
    int top;
    struct event events[APP_EVENT_STACK_SIZE];
};

static struct state state;


static void app_event_push(struct event* e)
{
    if (state.top < APP_EVENT_STACK_SIZE)
        state.events[state.top++] = (*e);
}


static bool app_event_pop(struct event* e)
{
    if (state.top) {
        (*e) = state.events[--state.top];
        return true;
    }
    return false;
}


static void app_glfw_key_cb(GLFWwindow* hwnd, int key, int code, int action, int mods)
{
    struct event e;
    switch (action) {
        case GLFW_PRESS:
            e.type = APP_KEY_DOWN;
            e.key  = key;
            e.mods = mods;
            break;
        default:
            break;
    }
    app_event_push(&e);
}


static void app_glfw_scroll_cb(GLFWwindow* hwnd, double dx, double dy)
{
    struct event e;
    e.type = APP_MOUSE_SCROLL;
    e.scroll[0] = dx;
    e.scroll[1] = dy;
    app_event_push(&e);
}


static void app_init_glfw(struct app* app)
{
    if (!glfwInit()) {
        fprintf(stderr, "[GLFW] initialisation failed\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    app->hwnd = glfwCreateWindow(app->width, app->height, app->title, NULL, NULL);

    glfwMakeContextCurrent(app->hwnd);
    glfwSwapInterval(app->swap_interval);
    glfwSetKeyCallback(app->hwnd, app_glfw_key_cb);
    glfwSetScrollCallback(app->hwnd, app_glfw_scroll_cb);

    if (gl3wInit()) {
        fprintf(stderr, "[GL3W] initialisation failed\n");
    }
    printf("OpenGL: %s\n", glGetString(GL_VERSION));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

}


static bool app_glfw_should_close(struct app* app)
{
    return glfwWindowShouldClose(app->hwnd);
}


static void app_glfw_flush(struct app* app)
{
    glfwPollEvents();
    glfwSwapBuffers(app->hwnd);
}


static void app_call_event(struct app* app)
{
    struct event e;
    while (app_event_pop(&e)) {
        if (app->event_cb) app->event_cb(&e);
    }
}


int app_run(struct app* app)
{
    app_init_glfw(app);
    if (app->init_cb) app->init_cb();

    while (!app_glfw_should_close(app)) {
        app_call_event(app);
        if (app->draw_cb) app->draw_cb();
        app_glfw_flush(app);
    };

    if (app->cleanup_cb) app->cleanup_cb();
    return 0;
}
