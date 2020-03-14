#include "util.h"
#include "square.h"
#include "shape.h"

int main()
{
   Square *s = Square__create(5, 10, 20, 20);
   ShapeType *type = Shape__type(Square__to_shape(s));
   const char *name = type->name(Square__to_shape(s));
   int sides = type->sides(Square__to_shape(s));
   int buffer_size = type->buffer_size;

   printf("name=%s, sides=%d, buffer_size=%d", name, sides, buffer_size);
   Shape__destroy(Square__to_shape(s));
   getchar();
   return 0;
}