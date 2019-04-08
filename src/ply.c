#include "ply.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENTS   16
#define MAX_PROPERTIES 32


struct property {
    char* name;
    int type;
    int itype;
    int vtype; /* value type */
};

struct element {
    char* name;
    int count;
    int num_properties;
    struct property properties[MAX_PROPERTIES];
    void* data;
    ply_read_cb* read_cb;
};

struct ply {
    FILE* fp;
    int format;
    int num_elements;
    struct element elements[MAX_ELEMENTS];
};


static const char* formats[] = {
    "ascii",
    "binary_big_endian",
    "binary_little_endian",
    NULL
};

static const char* types[] = {
    "int8",
    "uint8",
    "int16",
    "uint16",
    "int32",
    "uint32",
    "float32",
    "float64",
    "char",
    "uchar",
    "short",
    "ushort",
    "int",
    "uint",
    "float",
    "double",
    "list",
    NULL
};


static int string_to_enum(char* str, const char* list[])
{
    int i;
    for (i = 0; list[i]; ++i)
        if (!strcmp(str, list[i])) break;
    return i;
}


struct ply* ply_init()
{
    struct ply* pp = calloc(1, sizeof(struct ply));
    return pp;
}


void ply_free(struct ply* pp)
{
    for (int i = 0; i < pp->num_elements; ++i) {
        struct element* e = pp->elements + i;
        free(e->name);
        for (int j = 0; j < e->num_properties; ++j) {
            struct property* p = e->properties + j;
            free(p->name);
        }
    }
    free(pp);
}


void ply_init_io(struct ply* pp, FILE* fp)
{
    pp->fp = fp;
}


static struct element* ply_read_header_element(struct ply* pp)
{
    char* word = NULL;
    struct element* e = pp->elements + pp->num_elements;
    word = strtok(NULL, " \n");
    e->name = strdup(word);
    word = strtok(NULL, " \n");
    e->count = atoi(word);
    e->num_properties = 0;
    pp->num_elements++;
    return e;
}


static struct property* ply_read_header_property(struct ply* pp)
{
    char* word = NULL;
    struct element* e  = pp->elements + pp->num_elements - 1;
    struct property* p = e->properties + e->num_properties;
    word = strtok(NULL, " \n");
    p->type = string_to_enum(word, types);
    if (p->type == PLY_LIST) {
        word = strtok(NULL, " \n");
        p->itype = string_to_enum(word, types);
        word = strtok(NULL, " \n");
        p->vtype = string_to_enum(word, types);
    }
    word = strtok(NULL, " \n");
    p->name = strdup(word);
    e->num_properties++;
    return p;
}


void ply_read_header(struct ply* pp)
{
    char str[4096];
    fgets(str, 4096, pp->fp);
    if (!ply_check_sig(str, 3)) return;
    while (fgets(str, 4096, pp->fp)) {
        char* word = strtok(str, " \n");
        if (!strcmp(word, "format")) {
            word = strtok(NULL, " \n");
            pp->format = string_to_enum(word, formats);
        } else if (!strcmp(word, "element")) {
            struct element* e = ply_read_header_element(pp);
            if (!e) fprintf(stderr, "[ply] Invalid format\n");
        } else if (!strcmp(word, "property")) {
            struct property* p = ply_read_header_property(pp);
            if (!p) fprintf(stderr, "[ply] Invalid format\n");
        } else if (!strcmp(word, "comment")) {
            continue;
        } else if (!strcmp(word, "end_header")) {
            break;
        } else {
            fprintf(stderr, "[ply] Unexpected token %s\n", word);
            break;
        }
    }
}


bool ply_check_sig(const char* sig, int n)
{
    const char* magic = "ply";
    return !memcmp(magic, sig, n);
}


int ply_element_count(struct ply* pp, const char* name)
{
    for (int i = 0; i < pp->num_elements; ++i) {
        struct element* e = pp->elements + i;
        if (strcmp(e->name, name)) continue;
        return e->count;
    }
    return 0;
}


void ply_set_read_cb(struct ply* pp, const char* name, ply_read_cb read_cb, void* data)
{
    for (int i = 0; i < pp->num_elements; ++i) {
        struct element* e = pp->elements + i;
        if (strcmp(e->name, name)) continue;
        e->data = data;
        e->read_cb = read_cb;
    }
}


static double ply_read_property(struct ply* pp, struct element* e, struct property* p)
{
    double v = NAN;
    switch (pp->format) {
        case PLY_ASCII:
            fscanf(pp->fp, "%lf", &v);
            break;
        case PLY_BIG_ENDIAN:
        case PLY_LITTLE_ENDIAN:
            break;
    }
    return v;
}


static void ply_read_element(struct ply* pp, struct element* e)
{
    for (int i = 0; i < e->count; ++i) {
        for (int k = 0; k < e->num_properties; ++k) {
            struct property* p = e->properties + k;
            double v = ply_read_property(pp, e, p);
            e->read_cb(v, p->name, i, e->data);
        }
    }
}


void ply_read(struct ply* pp)
{
    for (int i = 0; i < pp->num_elements; ++i) {
        struct element* e = pp->elements + i;
        if (e->read_cb) ply_read_element(pp, e);
    }
}
