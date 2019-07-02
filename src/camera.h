#pragma once
#include <cglm/cglm.h>


struct camera {
    int width;
    int height;
    float fovy;
    float aspect;
    float znear;
    float zfar;
    float zoom;
    vec3 eye;
    vec3 center;
    vec3 up;
    vec3 right;
    vec3 front;
    vec3 bbox[2];
};

void camera_reset(struct camera* cam);
void camera_update(struct camera* cam);
