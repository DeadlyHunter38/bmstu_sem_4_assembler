#ifndef STRUCT_H
#define STRUCT_H

typedef struct vector vector_t;
struct vector
{
    size_t size;
    float vector[];
};

#endif