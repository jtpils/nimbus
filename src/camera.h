#pragma once
#include <cglm/cglm.h>

#define CAMERA_ASPECT_4_3 1.3333333333


enum {
    CAMERA_STILL,
    CAMERA_FORWARD,
    CAMERA_BACKWARD,
    CAMERA_LEFT,
    CAMERA_RIGHT,
};

struct camera {
    vec3 eye;
    vec3 dir;
    vec3 up;
    vec3 right;

    float fovy;
    float aspect;
    float znear;
    float zfar;

    float speed;
    float sensitivity;
};

void camera_reset(struct camera* cam);
void camera_move(struct camera* cam, int move, float dt);
void camera_zoom(struct camera* cam, float step);
