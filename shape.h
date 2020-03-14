#pragma once

// shape.h

struct Shapes;
struct ShapeTypes;
typedef struct Shapes Shape;
typedef struct ShapeTypes ShapeType;

struct Shapes
{
    ShapeType *type;
    char buffer_start;
};

struct ShapeTypes
{
    int buffer_size;
    const char *(*name)(Shape *);
    int (*sides)(Shape *);
    void (*destroy)(Shape *);
};


ShapeType *ShapeType__create(
    int buffer_size,
    const char *(*name)(Shape *),
    int (*sides)(Shape *),
    void (*destroy)(Shape *));
Shape *Shape__create(ShapeType* type);
ShapeType *Shape__type(Shape *self);
void *Shape__buffer(Shape *self);
int Shape__sides(Shape *self);
void Shape__destroy(Shape *shape);
