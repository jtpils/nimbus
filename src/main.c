#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "pcd.h"


struct pcd pcd;
struct camera cam;


static void init()
{
    pcd_setup_gl(&pcd);
}


static void input(struct event* e)
{
    if (e->type == APP_KEY_DOWN);
}


static void draw()
{
    vec4 color = {0.0f, 0.0f, 0.0f, 1.0f};
    int mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glw_clear(mask, color);
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
