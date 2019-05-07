#include "camera.h"


void camera_align(struct camera* cam, struct pcd* pcd)
{
    vec3 centroid = GLM_VEC3_ZERO_INIT;
    pcd_centroid(pcd, centroid);

    glm_vec3_add(centroid, GLM_ZUP, cam->eye);
    glm_vec3_copy(centroid, cam->center);
    glm_vec3_copy(GLM_YUP, cam->up);

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


void camera_view(struct camera* cam, mat4 view)
{
    glm_lookat(cam->eye, cam->center, cam->up, view);
}


void camera_proj(struct camera* cam, mat4 proj)
{
    float fovy = glm_rad(cam->fovy);
    glm_perspective(fovy, cam->aspect, cam->znear, cam->zfar, proj);
}
