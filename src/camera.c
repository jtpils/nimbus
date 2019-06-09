#include "camera.h"

#define CAMERA_DEFAULT_FOVY  45.0f
#define CAMERA_DEFAULT_ZNEAR 0.001f
#define CAMERA_DEFAULT_ZFAR  100.0f


void camera_reset(struct camera* cam)
{
    glm_vec3_zero(cam->eye);
    glm_vec3_negate_to(GLM_ZUP, cam->front);
    glm_vec3_copy(GLM_YUP, cam->up);
    glm_vec3_copy(GLM_XUP, cam->right);

    cam->eye[2] = 1.0f;
    cam->fovy  = CAMERA_DEFAULT_FOVY;
    cam->znear = CAMERA_DEFAULT_ZNEAR;
    cam->zfar  = CAMERA_DEFAULT_ZFAR;
}
