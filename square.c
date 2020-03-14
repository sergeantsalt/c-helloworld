#include <stdlib.h>
#include "square.h"
#include "shape.h"

// square.c
typedef struct SquareDatas
{
    int x;
    int y;
    int width;
    int height;
} SquareData;

const char *Square__name_override(Shape *self)
{
    return "Square";
}

int Square__sides_override(Shape *self)
{
    return 4;
}

void Square__destroy_override(Shape *square)
{
    free(square);
}

static ShapeType *square_type = (ShapeType *)NULL;
void Square_InitShapeType()
{
    square_type = ShapeType__create(
        sizeof(SquareData),
        &Square__name_override,
        &Square__sides_override,
        &Square__destroy_override);
}

Shape *Square__to_shape(Square *square)
{
    return ((Shape *)square);
}

Square *Square__from_shape(Shape *shape)
{
    if (!shape)
    {
        return ((Square *)0);
    }

    ShapeType *type = Shape__type(shape);
    if (type != square_type)
    {
        return ((Square *)0);
    }

    return ((Square *)shape);
}

SquareData *Square__square_data(Square *self)
{
    Shape *shape = (Shape *)self;
    return (SquareData *)Shape__buffer(shape);
}

Square *Square__create(int x, int y, int width, int height)
{
    if (square_type == NULL)
    {
        Square_InitShapeType();
    }

    Square *result = (Square *)Shape__create(square_type);
    SquareData *square_data = Square__square_data(result);
    square_data->x = x;
    square_data->y = y;
    square_data->width = width;
    square_data->height = height;
    return result;
}

void Square__destroy(Square *square)
{
    Shape__destroy(Square__to_shape(square));
}

int Square__x(Square *self)
{
    return Square__square_data(self)->x;
}

int Square__y(Square *self)
{
    return Square__square_data(self)->y;
}

int Square__width(Square *self)
{
    return Square__square_data(self)->width;
}

int Square__height(Square *self)
{
    return Square__square_data(self)->height;
}