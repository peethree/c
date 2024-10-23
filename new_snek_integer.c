#include <stdlib.h>

#include "snekobject.h"



snek_object_t *new_snek_integer(int value) {
  // allocate heap memory for a new pointer to a snek_object_t
  snek_object_t *snake_object = malloc(sizeof(snek_object_t));

  // if allocation fails: return null
  if (snake_object == NULL) {
    return NULL;
  }

  // set kind field of the object to INTEGER enum value
  snake_object->kind = INTEGER;

  // set v_int field to integer value passed in
  snake_object->data.v_int = value;

  // return point to the new snek object
  return snake_object;  
}


/////

typedef enum SnekObjectKind {
  INTEGER
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t *new_snek_integer(int value);
