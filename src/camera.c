#include "camera.h"

#define FOVY  45.0f
#define ZNEAR 0.001f
#define ZFAR  100.0f
#define ZOOM  0.7


void camera_reset(struct camera* cam)
{
    glm_vec3_copy(GLM_ZUP, cam->eye);
    glm_vec3_copy(GLM_YUP, cam->up);
    glm_vec3_copy(GLM_XUP, cam->right);
    glm_vec3_copy(GLM_ZUP, cam->front);
    glm_vec3_zero(cam->center);

    cam->fovy  = FOVY;
    cam->znear = ZNEAR;
    cam->zfar  = ZFAR;
    cam->zoom  = ZOOM;
}


void camera_update(struct camera* cam)
{
    float ratio = cam->zoom * glm_aabb_size(cam->bbox);
    float dist  = ratio / tanf(glm_rad(0.5 * cam->fovy));
    glm_aabb_center(cam->bbox, cam->center);
    glm_vec3_normalize(cam->front);
    glm_vec3_scale(cam->front, dist, cam->front);
    glm_vec3_add(cam->center, cam->front, cam->eye);
}
