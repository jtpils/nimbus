#include "app.h"
#include <stdio.h>


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

    if (gl3wInit()) {
        fprintf(stderr, "[GL3W] initialisation failed\n");
    }
    printf("OpenGL: %s\n", glGetString(GL_VERSION));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}


static bool app_should_close_glfw(struct app* app)
{
    return glfwWindowShouldClose(app->hwnd);
}


static void app_flush_glfw(struct app* app)
{
    glfwPollEvents();
    glfwSwapBuffers(app->hwnd);
}


int app_run(struct app* app)
{
    app_init_glfw(app);
    if (app->init_cb) app->init_cb();

    while (!app_should_close_glfw(app)) {
        if (app->draw_cb) app->draw_cb();
        app_flush_glfw(app);
    };

    if (app->cleanup_cb) app->cleanup_cb();
    return 0;
}
