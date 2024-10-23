#include "stdlib.h"


void allocate_int(int **pointer_pointer, int value) {
  
  // Allocate memory for a single integer on the heap, and save it's address into a new pointer.
  int *pointer = malloc(sizeof(int));

  // Update the memory address that pointer_pointer is pointing to, to be the address of the new pointer.
  *pointer_pointer = pointer;

   if (*pointer_pointer == NULL) {
    return;
  }

  // Set the raw value of the integer that pointer_pointer now points to (well, that it points to through 2 address hops) to the value passed in.
  **pointer_pointer = value;
}
