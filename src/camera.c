#include "camera.h"


void camera_align(struct camera* cam, struct pcd* pcd)
{
    vec3 centroid = GLM_VEC3_ZERO_INIT;
    pcd_centroid(pcd, centroid);

    glm_vec3_add(centroid, GLM_ZUP, cam->eye);
    glm_vec3_sub(centroid, cam->eye, cam->dir);
    glm_vec3_copy(GLM_YUP, cam->up);
    glm_vec3_cross(cam->dir, cam->up, cam->right);

    cam->fovy = 45.0f;
    cam->aspect = CAMERA_ASPECT_4_3;
    cam->znear = 0.001f;
    cam->zfar  = 100.0f;
}


void camera_zoom(struct camera* cam, float factor)
{
    cam->fovy += factor;
    cam->fovy = cam->fovy <=  1.0f ?  1.0f : cam->fovy;
    cam->fovy = cam->fovy >= 60.0f ? 60.0f : cam->fovy;
}


void camera_move(struct camera* cam, float speed, int move)
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
    glm_vec3_scale(v, speed, v);
    glm_vec3_add(cam->eye, v, cam->eye);
}


void camera_view(struct camera* cam, mat4 view)
{
    glm_look(cam->eye, cam->dir, cam->up, view);
}


void camera_proj(struct camera* cam, mat4 proj)
{
    float fovy = glm_rad(cam->fovy);
    glm_perspective(fovy, cam->aspect, cam->znear, cam->zfar, proj);
}
