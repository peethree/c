#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

// stack->data is an array of pointers

void stack_push(stack_t *stack, void *obj) {
  // If the stack's count is equal to the stack's capacity
  if (stack->count == stack->capacity) {
    //double the stack's capacity
    stack->capacity *= 2;
    // reallocate enough memory for the stack's data using the new capacity 
    void **new_data = realloc(stack->data, stack->capacity * sizeof(void *));
    
    // if realloc fails, free the old data and return immediately
    if (new_data == NULL) {
      free(stack->data);
      return;
    }
    // if it succeeds, update the stack's data field to point to the new memory
    stack->data = new_data;
  }  
  
  // Add the new object to the top of the stack (the count-th element in the array)
  stack->data[stack->count] = obj;
  // Increment the stack's count  
  stack->count++;
}


stack_t *stack_new(size_t capacity) {
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(stack->capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}




//// snekstack.h

#include <stddef.h>

typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
void stack_push(stack_t *stack, void *obj);


////