#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *new_snek_array(size_t size) {
  // allocate memory for a pointer to a snek_object_t
  snek_object_t *snake_object = malloc(sizeof(snek_object_t));

  // failed allocation
  if (snake_object == NULL) {
    return NULL;
  }

  // allocate memory for a new pointer to an array of snek_objects
  // don't store the actual array, just a pointer to it.
  snek_object_t **elements = calloc(size, sizeof(snek_object_t *)); 

  // if memory allocation for the array pointer fails, free object and return NULL
  if (elements == NULL) {
    free(snake_object);
    return NULL;
  }

  // set kind to appropriate kind
  snake_object->kind = ARRAY;

  // create the snek_array_t struct and set size / elements fields  
  snake_object->data.v_array.size = size;
  snake_object->data.v_array.elements = elements;

  // return pointer to the new snek object
  return snake_object;
}



snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
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

///// .h

#include <stddef.h>

typedef struct SnekObject snek_object_t;

typedef struct {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;

typedef struct {
  size_t size;
  snek_object_t **elements;
} snek_array_t;

typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  VECTOR3,
  ARRAY,
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  float v_float;
  char *v_string;
  snek_vector_t v_vector3;
  snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t *new_snek_integer(int value);
snek_object_t *new_snek_float(float value);
snek_object_t *new_snek_string(char *value);
snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
);

snek_object_t *new_snek_array(size_t size);
