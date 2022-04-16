#include <stdio.h>
#include "string_st.h"

int main(int argc, char *argv[])
{
  STRING_ST *myNewString = NULL;
  STRING_ST *myString = new_empty_string_s(25);
  STRING_ST *myLatestString = new_string("Hello Sweetheart", 20);

  fill_string(myString, "This is the fill");

  printf("Test 1: %s\n", get_str_literal(myString));
  printf("Test 2: %s\n", get_str_literal(myNewString));
  printf("Test 3: %s with length: %ld and memlength: %ld\n", get_str_literal(myLatestString), get_str_length(myLatestString), get_str_memlength(myLatestString));
  append_char(myLatestString, 'X');
  append_char(myLatestString, 'Y');
  append_char(myLatestString, 'Z');
  append_char(myLatestString, '0');
  printf("Test 4: %s with length: %ld and memlength: %ld\n", get_str_literal(myLatestString), get_str_length(myLatestString), get_str_memlength(myLatestString));

  printf("Test error code: %s\n", get_str_error(0));

  return 0;
}
