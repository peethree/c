// char ** is a pointer to a char pointer

void swap_strings(char **a, char **b) {

  // store the pointer that *a is pointing to in a temporary variable
  char *temp = *a;
  // ssigns the pointer that *b is pointing to, to *a.
  *a = *b;
  // assigns the original pointer from *a (stored in temp) to *b
  *b = temp;
}
