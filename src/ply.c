#include "ply.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_ELEMENTS   16
#define MAX_PROPERTIES 32


struct property {
    char* name;
    int type;
    int itype; /* index type */
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
    struct element*  e = pp->elements + pp->num_elements - 1;
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


static double ply_read_scalar_ascii(struct ply* pp, int type)
{
    switch (type) {
        case PLY_CHAR:
        case PLY_INT8: {
            int8_t c;
            fscanf(pp->fp, "%hhd", &c);
            return c;
        }
        case PLY_UCHAR:
        case PLY_UINT8: {
            uint8_t c;
            fscanf(pp->fp, "%hhu", &c);
            return c;
        }
        case PLY_SHORT:
        case PLY_INT16: {
            int16_t s;
            fscanf(pp->fp, "%hd", &s);
            return s;
        }
        case PLY_USHORT:
        case PLY_UINT16: {
            uint16_t s;
            fscanf(pp->fp, "%hu", &s);
            return s;
        }
        case PLY_INT:
        case PLY_INT32: {
            int32_t i;
            fscanf(pp->fp, "%d", &i);
            return i;
        }
        case PLY_UINT:
        case PLY_UINT32: {
            uint32_t i;
            fscanf(pp->fp, "%u", &i);
            return i;
        }
        case PLY_FLOAT:
        case PLY_FLOAT32: {
            float f;
            fscanf(pp->fp, "%f", &f);
            return f;
        }
        case PLY_DOUBLE:
        case PLY_FLOAT64: {
            double f;
            fscanf(pp->fp, "%lf", &f);
            return f;
        }
    }
    return NAN;
}


static double ply_read_scalar_binary(struct ply* pp, int type)
{
    switch (type) {
        case PLY_CHAR:
        case PLY_INT8: {
            int8_t c;
            fread(&c, sizeof(int8_t), 1, pp->fp);
            return c;
        }
        case PLY_UCHAR:
        case PLY_UINT8: {
            uint8_t c;
            fread(&c, sizeof(uint8_t), 1, pp->fp);
            return c;
        }
        case PLY_SHORT:
        case PLY_INT16: {
            int16_t s;
            fread(&s, sizeof(int16_t), 1, pp->fp);
            return s;
        }
        case PLY_USHORT:
        case PLY_UINT16: {
            uint16_t s;
            fread(&s, sizeof(uint16_t), 1, pp->fp);
            return s;
        }
        case PLY_INT:
        case PLY_INT32: {
            int32_t i;
            fread(&i, sizeof(int32_t), 1, pp->fp);
            return i;
        }
        case PLY_UINT:
        case PLY_UINT32: {
            uint32_t i;
            fread(&i, sizeof(uint32_t), 1, pp->fp);
            return i;
        }
        case PLY_FLOAT:
        case PLY_FLOAT32: {
            float f;
            fread(&f, sizeof(float), 1, pp->fp);
            return f;
        }
        case PLY_DOUBLE:
        case PLY_FLOAT64: {
            double f;
            fread(&f, sizeof(double), 1, pp->fp);
            return f;
        }
    }
    return NAN;
}


static double ply_read_property(struct ply* pp, struct element* e, struct property* p, int type)
{
    double v = NAN;
    switch (pp->format) {
        case PLY_ASCII:
            v = ply_read_scalar_ascii(pp, type);
            break;
        case PLY_BIG_ENDIAN:
        case PLY_LITTLE_ENDIAN:
            v = ply_read_scalar_binary(pp, type);
            break;
    }
    return v;
}


static void ply_read_element(struct ply* pp, struct element* e)
{
    for (int i = 0; i < e->count; ++i) {
        for (int k = 0; k < e->num_properties; ++k) {
            struct property* p = e->properties + k;
            if (p->type != PLY_LIST) {
                double v = ply_read_property(pp, e, p, p->type);
                if (e->read_cb) e->read_cb(v, p->name, i, 1, 0, e->data);
            } else {
                int len = ply_read_property(pp, e, p, p->itype);
                for (int iv = 0; iv < len; ++iv) {
                    double v = ply_read_property(pp, e, p, p->vtype);
                    if (e->read_cb) e->read_cb(v, p->name, i, len, iv, e->data);
                }
            }
        }
    }
}


void ply_read(struct ply* pp)
{
    for (int i = 0; i < pp->num_elements; ++i) {
        struct element* e = pp->elements + i;
        ply_read_element(pp, e);
    }
}
