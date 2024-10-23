#include <stdlib.h>

#include "exercise.h"

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
  token_t** token_pointers = (token_t**)malloc(count * sizeof(token_t*));
  if (token_pointers == NULL) {
    exit(1);
  }

  // allocate new space for each token on the heap, and store the address of the new space in the array.
  for (size_t i = 0; i < count; ++i) {
    token_t* new_token = (token_t*)malloc(sizeof(token_t));

    // check if allocation successful
    if (new_token == NULL) {
      exit(1);
    }

    // Copy the contents of the input struct into the newly allocated one.
    new_token->literal = tokens[i].literal; 
    new_token->line = tokens[i].line;
    new_token->column = tokens[i].column;

    // copy contents of input structs into newly allocated one
    token_pointers[i] = new_token;
  }
  
  return token_pointers;
}
