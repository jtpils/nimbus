#include "cloud.h"
#include "ply.h"


void cloud_load(struct cloud* pcd, const char* fname)
{
    FILE* fp = fopen(fname, "rb");
    struct ply* pp = ply_init();
    ply_init_io(pp, fp);
    ply_read_header(pp);
    pcd->size = ply_element_count(pp, "vertex");
    printf("%d\n", pcd->size);
    ply_free(pp);
    fclose(fp);
}
