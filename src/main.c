#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include "glw.h"
#include "app.h"
#include "pcd.h"


struct pcd pcd;


static void init()
{
}


static void draw()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
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
        .width = 800,
        .height = 600,
        .title = "nimbus"
    };
    return app_run(&app);
}
