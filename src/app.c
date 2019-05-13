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


static void app_flush(struct app* app)
{
    glfwPollEvents();
}


int app_run(struct app* app)
{
    app_init_gl(app);
    while (!app_should_close(app)) {
        if (app->redraw) app_draw(app);
        app_flush(app);
    }
    return 0;
}
