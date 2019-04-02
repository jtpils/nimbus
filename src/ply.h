#pragma once
#include <stdio.h>
#include <stdbool.h>


enum {
    PLY_ASCII,
    PLY_BIG_ENDIAN,
    PLY_LITTLE_ENDIAN,
};

enum {
    PLY_INT8,
    PLY_UINT8,
    PLY_INT16,
    PLY_UINT16,
    PLY_INT32,
    PLY_UINT32,
    PLY_FLOAT32,
    PLY_FLOAT64,
    PLY_CHAR,
    PLY_UCHAR,
    PLY_SHORT,
    PLY_USHORT,
    PLY_INT,
    PLY_UINT,
    PLY_FLOAT,
    PLY_DOUBLE,
    PLY_LIST,
};

struct ply;

struct ply* ply_init();
void ply_free(struct ply* pp);
void ply_init_io(struct ply* pp, FILE* fp);
void ply_read_header(struct ply* pp);
bool ply_check_sig(const char* sig, int n);
int  ply_element_count(struct ply* pp, const char* name);
