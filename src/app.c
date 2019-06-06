#include "app.h"
#include <stdio.h>
#include "render.h"

#define APP_STACK_SIZE 32


enum {
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_BUTTONS
};

struct state {
    int top;
    int width;
    int height;
    int draw_calls;
    double aspect;
    double origin[2];
    double cursor[2];
    bool redraw;
    bool mouse[MOUSE_BUTTONS];
    GLFWwindow* hwnd;
    struct model models[APP_STACK_SIZE];
    struct render renders[APP_STACK_SIZE];
};

static struct state state = {0};


static void app_resize_cb(GLFWwindow* win, int width, int height)
{
    state.width  = width;
    state.height = height;
    state.aspect = (float)width / (float)height;
    state.redraw = true;
}


static void app_key_cb(GLFWwindow* win, int key, int code, int action, int mods)
{
}


static void app_scroll_cb(GLFWwindow* win, double dx, double dy)
{
}


static void app_mouse_cb(GLFWwindow* win, int button, int action, int mods)
{
    double x, y;
    glfwGetCursorPos(win, &x, &y);

    switch (action) {
        case GLFW_PRESS:
            state.origin[0] = x;
            state.origin[1] = y;
            state.mouse[button] = true;
            break;
        case GLFW_RELEASE:
            state.cursor[0] = x;
            state.cursor[1] = y;
            state.mouse[button] = false;
            break;
    }
    state.redraw = true;
}


static void app_cursor_cb(GLFWwindow* win, double x, double y)
{
    state.cursor[0] = x;
    state.cursor[1] = y;
    /* rotating with left mouse */
    if (state.mouse[MOUSE_LEFT]) state.redraw = true;
    if (state.mouse[MOUSE_MIDDLE]) state.redraw = true;
}


static void app_init_gl(struct app* app)
{
    if (!glfwInit()) {
        fprintf(stderr, "[glfw] initilization failed.\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    state.hwnd = glfwCreateWindow(app->width, app->height, app->title, NULL, NULL);

    glfwSetKeyCallback(state.hwnd, app_key_cb);
    glfwSetScrollCallback(state.hwnd, app_scroll_cb);
    glfwSetCursorPosCallback(state.hwnd, app_cursor_cb);
    glfwSetMouseButtonCallback(state.hwnd, app_mouse_cb);
    glfwSetFramebufferSizeCallback(state.hwnd, app_resize_cb);

    int width, height;
    glfwMakeContextCurrent(state.hwnd);
    glfwSwapInterval(1);
    glfwGetFramebufferSize(state.hwnd, &width, &height);

    if (gl3wInit()) {
        fprintf(stderr, "[gl3w] initialization failed.\n");
    }
    printf("OpenGL: %s\n", glGetString(GL_VERSION));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    app_resize_cb(state.hwnd, width, height);
}


static void app_poll_events(struct app* app)
{
    glfwPollEvents();
}


static bool app_should_close(struct app* app)
{
    return glfwWindowShouldClose(state.hwnd);
}


static void app_draw(struct app* app)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(state.hwnd);

    state.redraw = false;
    state.draw_calls++;
}


void app_model_push(struct app* app, struct model* mod)
{
    if (state.top == APP_STACK_SIZE) {
        fprintf(stderr, "[nimbus] maximum stack size reached.\n");
        return;
    }
    /* initilize a new renderer and push the model into the stack */
    struct render* rnd = &state.renders[state.top];
    render_init(rnd, mod);
    state.models[state.top] = (*mod);
    state.top++;
}


int app_run(struct app* app)
{
    app_init_gl(app);

    while (!app_should_close(app)) {
        app_poll_events(app);
        if (!state.redraw) continue;
        app_draw(app);
    }

    return 0;
}
