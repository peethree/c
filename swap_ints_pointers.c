void swap_ints(int *a, int *b) {
  // temp now holds the value that a is pointing to
  int temp = *a;

  // update the value that a points to be *b
  *a = *b;

  // store the value from temp into the location that b points to.
  *b = temp;
}
