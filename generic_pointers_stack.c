#include "snekstack.h"
#include <stdlib.h>

stack_t *stack_new(size_t capacity) {
  // Allocate memory for a new Stack struct on the heap.
  stack_t *new_stack = malloc(sizeof(stack_t));

  // If allocation fails, return NULL.
  if (new_stack == NULL) {
    return NULL;
  }

  // Initialize the count to 0.
  new_stack->count = 0;

  // Initialize the capacity to the given value.
  new_stack->capacity = capacity;

  // Initialize the data by allocating enough memory for capacity number of void * pointers.
  new_stack->data = malloc(capacity * sizeof(void*));

  // If alloction fails, free the Stack struct and return NULL.
  if (new_stack->data == NULL) {
    free(new_stack);
    return NULL;  
  }

  // Return the new Stack struct.
  return new_stack;
}


// ----

#include <stddef.h>

typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
