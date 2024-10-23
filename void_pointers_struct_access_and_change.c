#include <stdlib.h>

#include "exercise.h"

void snek_zero_out(void *ptr, snek_object_kind_t kind){
  switch (kind) {
  // cast the void* to the appropriate struct pointer type in each case.
  case INTEGER:
    // accessed the value member using the arrow operator (->)
    ((snek_int_t*)ptr)->value = 0; // Set the value to 0 for each type.
    break; // used break statements to prevent fall-through in the switch cases.
  case FLOAT:
    ((snek_float_t*)ptr)->value = 0;
    break;
  case BOOL:
    ((snek_bool_t*)ptr)->value = 0;
    break;
  }
}


// ----
// exercise.h:

typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  BOOL,
} snek_object_kind_t;

typedef struct SnekInt {
  char *name;
  int value;
} snek_int_t;

typedef struct SnekFloat {
  char *name;
  float value;
} snek_float_t;

typedef struct SnekBool {
  char *name;
  unsigned int value;
} snek_bool_t;

void snek_zero_out(void *ptr, snek_object_kind_t kind);