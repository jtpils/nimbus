#include "app.h"
#include <stdio.h>

#define APP_STACK_SIZE 16


struct state {
    int top;
    int width;
    int height;
    float aspect;
    bool redraw;
    GLFWwindow* hwnd;

    struct event events[APP_STACK_SIZE];
};

static struct state state = {0};


static void app_resize_cb(GLFWwindow* win, int width, int height)
{
    state.width = width;
    state.height = height;
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
}


static void app_cursor_cb(GLFWwindow* win, double x, double y)
{
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


static void app_handle_events(struct app* app)
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
}


int app_run(struct app* app)
{
    app_init_gl(app);
    if (app->init_cb) app->init_cb();

    while (!app_should_close(app)) {
        app_handle_events(app);
        if (!state.redraw) continue;
        if (app->draw_cb) app->draw_cb();
        app_draw(app);
    }

    if (app->close_cb) app->close_cb();
    return 0;
}
