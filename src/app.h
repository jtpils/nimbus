#pragma once
#include "mesh.h"


struct app {
    int width;
    int height;
    char* title;
};

void app_model_push(struct app* app, struct mesh* msh);
void app_init(struct app* app);
int  app_run(struct app* app);
