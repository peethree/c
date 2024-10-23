#include <stdio.h>
#include <stdlib.h>

int *allocate_scalar_list(int size, int multiplier) {
  // allocate array of size integers on heap
  int *arr = malloc(size * sizeof(int));
  // handle allocation failing
  if (arr == NULL) {
    return NULL;
  }

  // initialize each element in the list to index * multiplier
  if (arr) {
    for (int i=0; i<size; i++) {
      arr[i] = i * multiplier;
    }
  }

  // return pointer
  return arr;  
}

// assume the calling code will call free on the returned pointer