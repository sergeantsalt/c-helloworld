#include <stdio.h>
#include <stdlib.h>

// typedef struct Shapes Shape;
// typedef struct ShapeTypes ShapeType;
// typedef struct Squares Square;
// typedef struct SquareDatas SquareData;

// shape.h
struct SquareData;
struct ShapeType;
typedef struct Squares Square;

ShapeType* ShapeType__create(
   int buffer_size,
   const char* (*name)(Shape*),
   int (*sides)(Shape*),
   void (*destroy)(Shape*));

Shape* Shape__create(ShapeType* type);
ShapeType* Shape__type(Shape* self);
void* Shape__buffer(Shape* self);
int Shape__sides(Shape* self);
void Shape__destroy(Shape* shape);

typedef struct Shapes{
   ShapeType* type;
   char buffer_start;
} Shape;

typedef struct ShapeTypes {
   int buffer_size;
   const char* (*name)(Shape*);
   int (*sides)(Shape*);
   void (*destroy)(Shape*);      
} ShapeType;

ShapeType* ShapeType__create(
     int buffer_size,
     const char* (*name)(Shape*),
     int (*sides)(Shape*),
     void (*destroy)(Shape*)) {
   ShapeType* result = (ShapeType*) malloc(sizeof(ShapeType));
   result->buffer_size = buffer_size;
   result->name = name;
   result->sides = sides;
   result->destroy = destroy;
   return result;
}

Shape* Shape__create(ShapeType* type) {
  int size = sizeof(Shape) + type->buffer_size;
  Shape* result = (Shape*) malloc(size);
  result->type = type;
  return result;
}

ShapeType* Shape__type(Shape* self) {
  return self->type;
}

void* Shape__buffer(Shape* self) {
   return (void*) &(self->buffer_start);
}

int Shape__sides(Shape* self) {
  return self->type->sides(self);
}

void Shape__destroy(Shape* shape) {
   if (shape) {
      shape->type->destroy(shape);
   }
}

// square.h
Square;
Shape* Square__to_shape(Square* square);
Square* Square__from_shape(Shape* shape);
Square* Square__create(int x, int y, int width, int height);
void Square__destroy(Square* square);

// Similar to the accessors in the prior case
int Square__x(Square* self);    
int Square__y(Square* self);    
int Square__width(Square* self);    
int Square__height(Square* self);    

// And its corresponding definition:

// square.c
typedef struct SquareDatas {
   int x;
   int y;
   int width;
   int height;
} SquareData;

const char* Square__name_override(Shape* self) {
   return "Square";
}

int Square__sides_override(Shape* self) {
   return 4;
}

void Square__destroy_override(Shape* square) {
   free(square);
}

static ShapeType* square_type = (ShapeType*)NULL;
void InitShapeTypes()
{
    square_type = ShapeType__create(
           sizeof(SquareData),
           &Square__name_override,
           &Square__sides_override,
           &Square__destroy_override);
}
    //    ShapeType__create(
    //        sizeof(SquareData),
    //        &Square__name_override,
    //        &Square__sides_override,
    //        &Square__destroy_override);

Shape* Square__to_shape(Square* square) {
   return ((Shape*) square);
}

Square* Square__from_shape(Shape* shape) {
  if (!shape)  {
    return ((Square*) 0);
  }

  ShapeType* type = Shape__type(shape);
  if (type != square_type) {
    return ((Square*) 0);
  }

  return ((Square*) shape);
}

SquareData* Square__square_data(Square* self) {
   Shape* shape = (Shape*) self;
   return (SquareData*) Shape__buffer(shape);
}

Square* Square__create(int x, int y, int width, int height) {
   Square* result = (Square*) Shape__create(square_type);
   SquareData* square_data = Square__square_data(result);
   square_data->x = x;
   square_data->y = y;
   square_data->width = width;
   square_data->height = height;
   return result;
}

void Square__destroy(Square* square) {
   Shape__destroy(Square__to_shape(square));
}

int Square__x(Square* self) {
   return Square__square_data(self)->x;
}

int Square__y(Square* self) {
   return Square__square_data(self)->y;
}   

int Square__width(Square* self) {
   return Square__square_data(self)->width;
}

int Square__height(Square* self) {
   return Square__square_data(self)->height;
}




int main()
{
    InitShapeTypes();
    Square* s = (Square*)Shape__create(square_type);
    ShapeType* type = Shape__type(Square__to_shape(s));
    const char* name = type->name(Square__to_shape(s));
    int sides = type->sides(Square__to_shape(s));
    int buffer_size = type->buffer_size;

    printf("name=%s, sides=%d, buffer_size=%d", name, sides, buffer_size);
    Shape__destroy(Square__to_shape(s));
    getchar();
    return 0;
}