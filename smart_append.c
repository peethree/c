#include <string.h>
#include "munit.h"

typedef struct {
  char buffer[64];
  size_t length;
} TextBuffer;


int smart_append(TextBuffer* dest, const char* src) {
  if (dest == NULL || src == NULL) {
    return 0;
  }
  // create constant to rep max buff size 64
  const int max_buffer = 64;

  // get length of src
  int length = strlen(src);

  // calc remaining space in dest buffer, - 1 for null char
  int remaining_space = max_buffer - dest->length - 1;  

  // if src string is larger than remaining space
  if (length > remaining_space) {
    // copy as much of the string into the buffer as possible with strncat     
    strncat(dest->buffer, src, remaining_space);
    // update dest buffer length to max size
    dest->length += remaining_space;
    return 0;
  } else {
  // otherwise: append entri src string to dest buffer
    strcat(dest->buffer, src);
    dest->length += length; 
    return 1;  
  }
}

munit_case(RUN, test_return_0_for_null_value, {
  TextBuffer dest;
  const char* src; 
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 0, "Should return 0 for null value");
});

munit_case(RUN, test_smart_append_empty_buffer, {
  TextBuffer dest;
  strcpy(dest.buffer, "");
  dest.length = 0;
  const char* src = "Hello";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 1, "Should return 1 for successful append");
  munit_assert_string_equal(dest.buffer, "Hello", "Buffer should contain 'Hello'");
  munit_assert_int(dest.length, ==, 5, "Length should be 5");
});

munit_case(SUBMIT, test_smart_append_full_buffer, {
  TextBuffer dest;
  strcpy(dest.buffer, "This is a very long string that will fill up the entire buffer.");
  dest.length = 63;
  const char* src = " Extra";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 0, "Should return 0 for unsuccessful append");
  munit_assert_string_equal(dest.buffer, "This is a very long string that will fill up the entire buffer.", "Buffer should remain unchanged");
  munit_assert_int(dest.length, ==, 63, "Length should remain 63");
});

munit_case(SUBMIT, test_smart_append_overflow, {
  TextBuffer dest;
  strcpy(dest.buffer, "This is a long string");
  dest.length = 21;
  const char* src = " that will fill the whole buffer and leave no space for some of the chars.";
  int result = smart_append(&dest, src);
  munit_assert_int(result, ==, 0, "Should return 0 for overflow append");
  munit_assert_string_equal(dest.buffer, "This is a long string that will fill the whole buffer and leave", "Buffer should be filled to capacity");
  munit_assert_int(dest.length, ==, 63, "Length should be 63 after overflow append");
});

int main() {
  MunitTest tests[] = {
    munit_test("/test_return_0_for_null_value", test_return_0_for_null_value),
    munit_test("/test_smart_append_empty_buffer", test_smart_append_empty_buffer),
    munit_test("/test_smart_append_full_buffer", test_smart_append_full_buffer),
    munit_test("/test_smart_append_overflow", test_smart_append_overflow),
    munit_null_test,
  };

  MunitSuite suite = munit_suite("smart_append", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}



