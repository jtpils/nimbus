#pragma once
#include <cglm/cglm.h>


struct camera {
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;

    float yaw;
    float pitch;

    float speed;
    float sensitivity;
    float fov;
};


void camera_view_matrix(struct camera* cam, mat4 view);
void camera_update(struct camera* cam);
void camera_move(struct camera* cam, float dx, float dy);
void camera_zoom(struct camera* cam, float dx, float dy);
