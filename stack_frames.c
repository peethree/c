#include "vm.h"

void vm_frame_push(vm_t *vm, frame_t *frame) {
  // stack_push a frame_t * onto the vm->frames stack
  // void stack_push(stack_t *stack, void *obj) 
  stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm) {
  // allocate new frame
  frame_t *new_frame = malloc(sizeof(frame_t));
  
  // initialize frame's references with a capacity of 8
  new_frame->references = stack_new(8);

  //push the newly allocated frame onto the vm->frames stack
  // void stack_push(stack_t *stack, void *obj) {
  vm_frame_push(vm, new_frame);
  //return new frame
  return new_frame;    
}

void frame_free(frame_t *frame) {
  // free frame_t's references
  // void stack_free(stack_t *stack) {
  stack_free(frame->references);
  // free frame_t struct
  free(frame);
}


vm_t *vm_new() {
  vm_t *vm = malloc(sizeof(vm_t));
  if (vm == NULL) {
    return NULL;
  }

  vm->frames = stack_new(8);
  vm->objects = stack_new(8);
  return vm;
}

void vm_free(vm_t *vm) {
  for (int i = 0; i < vm->frames->count; i++) {
    frame_free(vm->frames->data[i]);
  }
  stack_free(vm->frames);
  stack_free(vm->objects);
  free(vm);
}
