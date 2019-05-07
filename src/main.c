#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "pcd.h"


struct pcd pcd;
struct camera cam;

vec2  origin;
vec2  cursor;
float prev = 0.0f;
float speed = 1.0f;
bool  rotate = false;
bool  move[CAMERA_NUM_DIRECTION] = {0};


static void init()
{
    pcd_setup_gl(&pcd);
    camera_align(&cam, &pcd);
}


static void input(struct event* e)
{
    switch (e->type) {
        case APP_KEY_DOWN:
            if (e->key == GLFW_KEY_W) move[CAMERA_FORWARD]  = true;
            if (e->key == GLFW_KEY_S) move[CAMERA_BACKWARD] = true;
            if (e->key == GLFW_KEY_A) move[CAMERA_LEFT]     = true;
            if (e->key == GLFW_KEY_D) move[CAMERA_RIGHT]    = true;
            break;
        case APP_KEY_UP:
            if (e->key == GLFW_KEY_W) move[CAMERA_FORWARD]  = false;
            if (e->key == GLFW_KEY_S) move[CAMERA_BACKWARD] = false;
            if (e->key == GLFW_KEY_A) move[CAMERA_LEFT]     = false;
            if (e->key == GLFW_KEY_D) move[CAMERA_RIGHT]    = false;
            break;
        case APP_MOUSE_SCROLL:
            camera_zoom(&cam, e->scroll[1]);
            break;
        case APP_MOUSE_CURSOR:
            cursor[0] = e->pos[0];
            cursor[1] = e->pos[1];
            break;
        case APP_MOUSE_DOWN:
            rotate = true;
            origin[0] = e->pos[0];
            origin[1] = e->pos[1];
            break;
        case APP_MOUSE_UP:
            rotate = false;
            break;
        default: break;
    }
}


static void draw()
{
    vec4 color = {0.0f, 0.0f, 0.0f, 1.0f};
    int mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glw_clear(mask, color);

    float now = app_get_time();
    float dt = now - prev;
    for (int i = 0; i < CAMERA_NUM_DIRECTION; ++i)
        if (move[i]) camera_move(&cam, speed * dt, i);
    prev = now;

    mat4 proj, view;
    camera_proj(&cam, proj);
    camera_view(&cam, view);
    glm_mat4_mul(proj, view, pcd.mvp);

    pcd_draw(&pcd);
}


static void cleanup()
{
    pcd_free(&pcd);
}


int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: nimbus [filename]\n");
        return 0;
    }

    const char* fname = argv[1];
    pcd_load(&pcd, fname);

    struct app app = {
        .init_cb = init,
        .draw_cb = draw,
        .cleanup_cb = cleanup,
        .error_cb = NULL,
        .event_cb = input,
        .width = 800,
        .height = 600,
        .title = "nimbus",
        .swap_interval = 1
    };
    return app_run(&app);
}
