#include "camera.h"
#include <stdio.h>


void camera_reset(struct camera* cam)
{
    glm_vec3_zero(cam->eye);
    glm_vec3_copy(GLM_YUP, cam->up);
    cam->yaw = -90.0f;
    cam->pitch = 0.0f;
    cam->fovy = 45.0f;
    cam->aspect = CAMERA_ASPECT_4_3;
    cam->znear = 0.001f;
    cam->zfar  = 100.0f;
    cam->sensitivity = 0.5f;
    camera_sync(cam);
}


void camera_sync(struct camera* cam)
{
    float yaw   = glm_rad(cam->yaw);
    float pitch = glm_rad(cam->pitch);
    cam->dir[0] = cosf(yaw) * cosf(pitch);
    cam->dir[1] = sinf(pitch);
    cam->dir[2] = sinf(yaw) * cosf(pitch);
    glm_normalize(cam->dir);
    glm_cross(cam->dir, GLM_YUP, cam->right);
    glm_cross(cam->right, cam->dir, cam->up);
}


void camera_move(struct camera* cam, float step, int dir)
{
    vec3 delta;
    switch (dir) {
        case CAMERA_FORWARD:
            glm_vec3_copy(cam->dir, delta);
            break;
        case CAMERA_BACKWARD:
            glm_vec3_negate_to(cam->dir, delta);
            break;
        case CAMERA_RIGHT:
            glm_vec3_copy(cam->right, delta);
            break;
        case CAMERA_LEFT:
            glm_vec3_negate_to(cam->right, delta);
            break;
    }
    glm_vec3_scale(delta, step, delta);
    glm_vec3_add(cam->target, delta, cam->target);
}


void camera_zoom(struct camera* cam, float step)
{
    cam->fovy += cam->sensitivity * step;
    cam->fovy = cam->fovy <=  1.0f ?  1.0f : cam->fovy;
    cam->fovy = cam->fovy >= 45.0f ? 45.0f : cam->fovy;
}
