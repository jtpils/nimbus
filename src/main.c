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
    return app_run(&app);
}
