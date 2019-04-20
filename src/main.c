#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "pcd.h"


struct pcd pcd;
struct camera cam;

float prev = 0.0f;

bool move[CAMERA_NUM_DIRECTION] = {0};


static void init()
{
    pcd_setup_gl(&pcd);
    camera_reset(&cam);
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
        default:
            break;
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
        if (move[i]) camera_move(&cam, i, dt);
    prev = now;

    mat4 proj, view; /* update MVP */
    float fovy = glm_rad(cam.fovy);
    glm_perspective(fovy, cam.aspect, cam.znear, cam.zfar, proj);
    glm_look(cam.eye, cam.dir, cam.up, view);
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
