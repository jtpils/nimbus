#include "pcd.h"
#include "ply.h"


void pcd_load(struct pcd* pcd, const char* fname)
{
    FILE* fp = fopen(fname, "rb");
    struct ply* p = ply_init();

    ply_init_io(p, fp);
    ply_read_header(p);

    ply_free(p);
    fclose(fp);
}
