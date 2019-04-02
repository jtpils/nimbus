#include <stdio.h>
#include <stdlib.h>

#define GL_SILENCE_DEPRECATION
#include "app.h"
#include "pcd.h"


struct pcd pcd;


static void init(void)
{
}


static void draw(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char* argv[])
{
    const char* fname = argv[1];
    pcd_load(&pcd, fname);

    struct app app = {
        .init_cb = init,
        .draw_cb = draw,
        .cleanup_cb = NULL,
        .error_cb = NULL,
        .width = 800,
        .height = 600,
        .title = "nimbus"
    };
    return app_run(&app);
}
