#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "pcd.h"


int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: nimbus [filename]\n");
        return 0;
    }

    struct pcd pcd = {0};
    pcd_load(&pcd, argv[1]);

    struct app app = {
        .width = 800,
        .height = 600,
        .title = "nimbus",
        .swap_interval = 1
    };
    return app_run(&app);
}
