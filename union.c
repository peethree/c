#include <stdio.h>

typedef enum {
  INTEGER = 0,
  STRING = 1,
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  char *v_string;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t new_integer(int);
snek_object_t new_string(char *str);
void format_object(snek_object_t obj, char *buffer);


void format_object(snek_object_t obj, char *buffer) {
  switch (obj.kind) {
    case INTEGER:      
      sprintf(buffer, "int:%d", obj.data.v_int);   
      break;
    case STRING:
      sprintf(buffer, "string:%s", obj.data.v_string);
      break;
    default:
      printf("neither int nor string");
  }
}

snek_object_t new_integer(int i) {
  return (snek_object_t){
    .kind = INTEGER,
    .data = {.v_int = i}
  };
}

snek_object_t new_string(char *str) {  
  return (snek_object_t){
    .kind = STRING,
    .data = {.v_string = str}
  };
}

