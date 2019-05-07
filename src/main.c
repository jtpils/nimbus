#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "pcd.h"


struct pcd pcd;
struct camera cam;

bool  rotate = false;
vec2  origin;
vec2  cursor;
float prev = 0.0f;


static void init()
{
    pcd_setup_gl(&pcd);
    camera_align(&cam, &pcd);
}


static void input(struct event* e)
{
    switch (e->type) {
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
