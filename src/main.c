#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "pcd.h"


struct pcd pcd;
struct camera cam;
float velocity = 0.1f;


static void init()
{
    pcd_setup_gl(&pcd);
    camera_reset(&cam);
}


static void input(struct event* e)
{
    switch (e->type) {
        case APP_KEY_DOWN:
            if (e->key == GLFW_KEY_W) camera_move(&cam, CAMERA_FORWARD, velocity);
            else if (e->key == GLFW_KEY_S) camera_move(&cam, CAMERA_BACKWARD, velocity);
            else if (e->key == GLFW_KEY_A) camera_move(&cam, CAMERA_LEFT, velocity);
            else if (e->key == GLFW_KEY_D) camera_move(&cam, CAMERA_RIGHT, velocity);
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

    mat4 proj, view;
    glm_perspective(cam.fovy, cam.aspect, cam.znear, cam.zfar, proj);
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
        .title = "nimbus"
    };
    return app_run(&app);
}
