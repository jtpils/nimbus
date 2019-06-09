#include "app.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "model.h"
#include "shader.h"
#include "camera.h"

#define APP_STACK_SIZE 32


enum {
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_BUTTONS
};

struct state {
    int size;
    int draw_calls;
    double origin[2];
    double cursor[2];
    GLFWwindow* hwnd;
    unsigned int shader;
    unsigned int models[APP_STACK_SIZE];
    struct mesh* meshes[APP_STACK_SIZE];
    bool redraw;
    bool mouse[MOUSE_BUTTONS];
};


static struct state state = {0};
static struct camera cam = {0};


static void app_resize_cb(GLFWwindow* win, int width, int height)
{
    cam.width  = width;
    cam.height = height;
    cam.aspect = (float)width / (float)height;
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

    mat4 view, proj, mvp;
    glm_perspective(glm_rad(cam.fovy), cam.aspect, cam.znear, cam.zfar, proj);
    glm_look(cam.eye, cam.front, cam.up, view);
    glm_mat4_mul(proj, view, mvp);

    struct uniform argv[] = {
        [0] = {.name = "mvp", .type = GL_MAT4, .data = (float*)mvp}
    };
    shader_bind(state.shader);
    shader_args(state.shader, 1, argv);

    for (int i = 0; i < state.size; ++i) {
        struct mesh* msh = state.meshes[i];
        unsigned int mdl = state.models[i];
        model_draw(mdl, GL_POINTS, 0, msh->vc);
    };

    state.draw_calls++;
    state.redraw = false;
    glfwSwapBuffers(state.hwnd);
}


void app_init(struct app* app)
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
    state.shader = shader_init();
    camera_reset(&cam);
}


void app_model_push(struct app* app, struct mesh* msh)
{
    if (state.size == APP_STACK_SIZE) {
        fprintf(stderr, "[nimbus] maximum stack size reached.\n");
        return;
    }
    state.meshes[state.size] = msh;
    state.models[state.size] = model_init(msh);
    state.size++;
}


int app_run(struct app* app)
{
    while (!app_should_close(app)) {
        app_poll_events(app);
        if (!state.redraw) continue;
        app_draw(app);
    }

    return 0;
}
