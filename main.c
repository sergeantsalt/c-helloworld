#include "util.h"
#include "square.h"
#include <gsl/gsl_cdf.h>
// #include "shape.h"

int main()
{
   double bottom_tail = gsl_cdf_gaussian_P(-1.96, 1);
   printf("Area between [-1.96, 1.96]: %g\n", 1-2*bottom_tail);
   return 0;

   Square *s = Square__create(5, 10, 20, 20);
   Shape *shape = Square__to_shape(s);
   ShapeType *type = Shape__type(shape);
   const char *name = type->name(shape);
   int sides = type->sides(shape);
   int buffer_size = type->buffer_size;

   printf("name=%s, sides=%d, buffer_size=%d", name, sides, buffer_size);
   Shape__destroy(Square__to_shape(s));
   getchar();
   return 0;
}