#include <stdlib.h>
#include <string.h>

void swap(void *vp1, void *vp2, size_t size) {

  // Allocate memory for a temporary buffer to store the data using malloc.
  void *temp = malloc(size);

  // If the allocation fails (returns NULL) return immediately.
  if (temp == NULL) {
    return; 
  }

  // Use memcpy to shuffle the data around.
  // void *memcpy(void *destination, void* source, size_t size);
  memcpy(temp, vp1, size);
  memcpy(vp1, vp2, size);
  memcpy(vp2, temp, size);

  // free temp buffer
  free(temp);
}