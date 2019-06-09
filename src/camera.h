#pragma once
#include <cglm/cglm.h>


struct camera {
    int width;
    int height;
    float fovy;
    float aspect;
    float znear;
    float zfar;
    vec3 eye;
    vec3 front;
    vec3 up;
    vec3 right;
};

void camera_reset(struct camera* cam);
