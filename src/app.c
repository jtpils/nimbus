#include "app.h"
#include <stdio.h>


static void app_resize_cb(GLFWwindow* win, int width, int height)
{
    struct app* app = (struct app*)glfwGetWindowUserPointer(win);
    app->width = width;
    app->height = height;
    app->aspect = (float)width / (float)height;
    app->redraw = true;
}


static void app_key_cb(GLFWwindow* win, int key, int code, int action, int mods)
{
    struct app* app = (struct app*)glfwGetWindowUserPointer(win);
    app->redraw = true;
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
        fprintf(stderr, "[GLFW] initialisation failed.\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    app->hwnd = glfwCreateWindow(app->width, app->height, app->title, NULL, NULL);

    int width, height;
    glfwSetKeyCallback(app->hwnd, app_key_cb);
    glfwSetScrollCallback(app->hwnd, app_scroll_cb);
    glfwSetCursorPosCallback(app->hwnd, app_cursor_cb);
    glfwSetMouseButtonCallback(app->hwnd, app_mouse_cb);
    glfwSetWindowUserPointer(app->hwnd, app);
    glfwMakeContextCurrent(app->hwnd);
    glfwSwapInterval(app->swap_interval);
    glfwGetFramebufferSize(app->hwnd, &width, &height);

    if (gl3wInit()) {
        fprintf(stderr, "[GL3W] initialisation failed.\n");
    }
    printf("OpenGL: %s\n", glGetString(GL_VERSION));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    app_resize_cb(app->hwnd, width, height);
}


static bool app_should_close(struct app* app)
{
    return glfwWindowShouldClose(app->hwnd);
}


static void app_draw(struct app* app)
{

}


int app_run(struct app* app)
{
    app_init_gl(app);
    while (!app_should_close(app)) {
        app_draw(app);
    }
    return 0;
}
