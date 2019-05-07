#pragma once
#include <cglm/cglm.h>
#include "pcd.h"


#define CAMERA_ASPECT_4_3 1.3333333333


struct camera {
    vec3 eye;
    vec3 up;
    vec3 center;
    vec4 ori;

    float fovy;
    float aspect;
    float znear;
    float zfar;
};


void camera_align(struct camera* cam, struct pcd* pcd);
void camera_zoom(struct camera* cam, float factor);

void camera_proj(struct camera* cam, mat4 proj);
void camera_view(struct camera* cam, mat4 view);
