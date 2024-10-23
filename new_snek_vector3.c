#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z) {
  // if any of the inputs are null, return NULL
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  // allocate memory for new snek object pointer
  snek_object_t *snake_object = malloc(sizeof(snek_object_t));

  // allocation failure
  if (snake_object == NULL) {
    return NULL;
  }

  // set kind to appropriate enum
  snake_object->kind = VECTOR3;

  // create new snek_vector_t struct and set x, y, z fields to input pointers
  snek_vector_t snake_vector;
  snake_vector.x = x;
  snake_vector.y = y;
  snake_vector.z = z;

  // set the v_vector3 field of the new snek object to the newly created snek_vector_t
  snake_object->data.v_vector3 = snake_vector;

  // return the pointer to new snek object
  return snake_object;  
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value);
  char *dst = malloc(len + 1);
  if (dst == NULL) {
    free(obj);
    return NULL;
  }

  strcpy(dst, value);

  obj->kind = STRING;
  obj->data.v_string = dst;
  return obj;
}


//// snekobject.h

//forward declaration to break circular dependency between snek_vector_t and snek_object_t
typedef struct SnekObject snek_object_t;

typedef struct {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;


typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  VECTOR3,
} snek_object_kind_t;


typedef union SnekObjectData {
  int v_int;
  float v_float;
  char *v_string;
  snek_vector_t v_vector3;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;


snek_object_t *new_snek_integer(int value);
snek_object_t *new_snek_float(float value);
snek_object_t *new_snek_string(char *value);
snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z);
