#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *new_snek_string(char *value) {
  //allocate memory for a new pointerto snek_object_t
  snek_object_t *snake_object = malloc(sizeof(snek_object_t));

  // failed allocation
  if (snake_object == NULL) {
    return NULL;
  }

  // calculate length of string passed in
  int length = strlen(value) + 1;

  //allocate memory in a char * field equal to the length of string + 1 
  char *new_string = malloc(sizeof(char) * length);

  // failed allocation
  if (new_string == NULL) {
    return NULL;
  }

  // copy data from input value to new string field
  strcpy(new_string, value);

  // set kind field to string enum
  snake_object->kind = STRING;

  // store the newly allocated string in the object
  snake_object->data.v_string = new_string;

  // return pointer to new snek object
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


/// snekobject.h

typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  STRING,
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  float v_float;
  char * v_string;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t *new_snek_integer(int value);
snek_object_t *new_snek_float(float value);
snek_object_t *new_snek_string(char *value);
