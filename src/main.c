#include <stdio.h>
#include <stdlib.h>
#include "app.h"


int main(int argc, char* argv[])
{
    struct app app = {
        .width = 800,
        .height = 600,
        .title = "nimbus",
    };

    if (argc > 1) {
        struct mesh msh = {0};
        mesh_load(&msh, argv[1]);
        app_model_push(&app, &msh);
    }

    return app_run(&app);
}
