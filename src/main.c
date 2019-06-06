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
        struct model mod;
        model_load(&mod, argv[1]);
        app_model_push(&app, &mod);
    }

    return app_run(&app);
}
