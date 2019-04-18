#pragma once
#include <cglm/cglm.h>

#define CAMERA_ASPECT_4_3 1.3333333333


enum {
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
    vec3 target;

    float yaw;
    float pitch;

    float fovy;
    float aspect;
    float znear;
    float zfar;

    float sensitivity;
};

void camera_reset(struct camera* cam);
void camera_sync(struct camera* cam);
void camera_move(struct camera* cam, float step, int dir);
void camera_zoom(struct camera* cam, float step);
