#pragma once
#include <cglm/cglm.h>
#include "pcd.h"


#define CAMERA_ASPECT_4_3 1.3333333333

enum {
    CAMERA_FORWARD,
    CAMERA_BACKWARD,
    CAMERA_LEFT,
    CAMERA_RIGHT,
    CAMERA_NUM_DIRECTION,
};


struct camera {
    vec3 eye;
    vec3 up;
    vec3 dir;
    vec3 right;

    float fovy;
    float aspect;
    float znear;
    float zfar;
};


void camera_align(struct camera* cam, struct pcd* pcd);
void camera_move(struct camera* cam, float speed, int move);
void camera_zoom(struct camera* cam, float factor);

void camera_proj(struct camera* cam, mat4 proj);
void camera_view(struct camera* cam, mat4 view);
