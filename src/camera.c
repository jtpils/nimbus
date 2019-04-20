#include "camera.h"
#include <stdio.h>


void camera_reset(struct camera* cam)
{
    glm_vec3_zero(cam->eye);
    glm_vec3_negate_to(GLM_ZUP, cam->dir);
    glm_cross(cam->dir, GLM_YUP, cam->right);
    glm_cross(cam->right, cam->dir, cam->up);
    cam->fovy = 45.0f;
    cam->aspect = CAMERA_ASPECT_4_3;
    cam->znear = 0.001f;
    cam->zfar  = 100.0f;
    cam->speed = 1.0f;
}


void camera_move(struct camera* cam, int move, float dt)
{
    vec3 v;
    switch (move) {
        case CAMERA_FORWARD:
            glm_vec3_copy(cam->dir, v);
            break;
        case CAMERA_BACKWARD:
            glm_vec3_negate_to(cam->dir, v);
            break;
        case CAMERA_RIGHT:
            glm_vec3_copy(cam->right, v);
            break;
        case CAMERA_LEFT:
            glm_vec3_negate_to(cam->right, v);
            break;
    }
    glm_vec3_scale(v, cam->speed * dt, v);
    glm_vec3_add(cam->eye, v, cam->eye);
}


void camera_zoom(struct camera* cam, float factor)
{
    cam->fovy += factor;
    cam->fovy = cam->fovy <=  1.0f ?  1.0f : cam->fovy;
    cam->fovy = cam->fovy >= 45.0f ? 45.0f : cam->fovy;
}
