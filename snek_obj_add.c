#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  // either input is NULL
  if (a == NULL || b == NULL) {
    return NULL;
  }

  // if a is an integer:
  if (a->kind == INTEGER) {
    // b is an integer
    if (b->kind == INTEGER) {      
      return new_snek_integer(a->data.v_int + b->data.v_int);
    }
    // b is a float
    if (b->kind == FLOAT) {      
      return new_snek_float((float)a->data.v_int + b->data.v_float);
    }
    // any other case
    return NULL;    
  }

  if (a->kind == FLOAT) {
    if (b->kind == INTEGER) {      
      return new_snek_float(a->data.v_float + (float)b->data.v_int);
    }
    if (b->kind == FLOAT) {
      return new_snek_float(a->data.v_float + b->data.v_float);
    }
    return NULL;
  }

  // a is a string
  if (a->kind == STRING) {
    // b is not a string
    if (b->kind != STRING) {
      return NULL;
    }
    // otherwise:

    // length of a + b, added 1 for null character
    int length_ab = snek_length(a) + snek_length(b) + 1;
    
    // allocate memory for temporary string with calloc
    char *temp_string = calloc(length_ab, sizeof(char));

    // memory allocation failure
    if (temp_string == NULL) {
      return NULL;
    }
    
    // append data from a and then b to temporary string
    strcat(temp_string, a->data.v_string);
    strcat(temp_string, b->data.v_string);

    // create new snek_string, pass in temp string
    snek_object_t *snek_string = new_snek_string(temp_string);
    
    // free temp string memory and return new string object
    free(temp_string);
    return snek_string;
  }
  
  // if a is a vector3
  if (a->kind == VECTOR3) {
    // if b isn't a vector3
    if (b->kind != VECTOR3) {
      return NULL;
    }
    // otherwise:

    // create new snek vector3 and recursively call snek_add foreach of the x, y and z fields 
    snek_object_t *new_x = snek_add(a->data.v_vector3.x, b->data.v_vector3.x);
    snek_object_t *new_y = snek_add(a->data.v_vector3.y, b->data.v_vector3.y);
    snek_object_t *new_z = snek_add(a->data.v_vector3.z, b->data.v_vector3.z);

    snek_object_t *snek_vector3 = new_snek_vector3(new_x, new_y, new_z);

    return snek_vector3;
  }  

  // if a is an array
  if (a->kind == ARRAY) {
    // if b isn't an array
    if (b->kind != ARRAY) {
      return NULL;
    }
    //otherwise:

    // create new snek array with the combined length of a and b    
    int length_a = snek_length(a);
    int length_b = snek_length(b);
    int length_ab = length_a + length_b;
    
    snek_object_t *new_array = new_snek_array(length_ab);

    // iterate over each index in a and use set and get functions to copy the values from a and b to the new array
    for (int i = 0; i < snek_length(a); i++) {      
      snek_object_t *val = snek_array_get(a, i);
      snek_array_set(new_array, i, val);
    }
    // same for b, start at index length_a to not overwrite the values set previously.
    for (int i = 0; i < snek_length(b); i++) {
      snek_object_t *val = snek_array_get(b, i);
      snek_array_set(new_array, length_a + i, val);
    }
    // return new array object
    return new_array;
  }
  // if a is none of the above, invalid operation
  return NULL;  
}

int snek_length(snek_object_t *obj) {
  if (obj == NULL) {
    return -1;
  }

  switch (obj->kind) {
  case INTEGER:
    return 1;
  case FLOAT:
    return 1;
  case STRING:
    return strlen(obj->data.v_string);
  case VECTOR3:
    return 3;
  case ARRAY:
    return obj->data.v_array.size;
  default:
    return -1;
  }
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
  return obj;
}

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
  if (array == NULL || value == NULL) {
    return false;
  }

  if (array->kind != ARRAY) {
    return false;
  }

  if (index >= array->data.v_array.size) {
    return false;
  }

  // Set the value directly now (already checked size constraint)
  array->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *array, size_t index) {
  if (array == NULL) {
    return NULL;
  }

  if (array->kind != ARRAY) {
    return NULL;
  }

  if (index >= array->data.v_array.size) {
    return NULL;
  }

  // Set the value directly now (already checked size constraint)
  return array->data.v_array.elements[index];
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
