#include "vm.h"

vm_t *vm_new() {
  // allocate memory for new vm_t struct
  vm_t *new_vm = malloc(sizeof(vm_t));

  // initialize frames with a capacity of 8
  // objects stack with a capacity of 8 using the stack_new func
  new_vm->frames = stack_new(8);  
  new_vm->objects = stack_new(8);
   
  return new_vm;  
}

void vm_free(vm_t *vm) {
  // void stack_free(stack_t *stack) {
  stack_free(vm->frames);
  stack_free(vm->objects);
  free(vm);
}



//// vm.c