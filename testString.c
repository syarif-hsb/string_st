#include <stdio.h>
#include "string_st.h"

void test_concat()
{
  printf("\n====== TEST CONCAT ======\n");

  STRING_ST *str1 = new_string("Hello Sweetheart", 20);
  STRING_ST *str2 = new_empty_string_s(256);
  STRING_ST *str3 = new_empty_string();
  STRING_ST *str4 = new_string("Hello There", 20);

  STRING_ST *result = concat_str(4, str1, str2, str3, str4);

  printf("Concat result: %s\n", get_str_literal(result));

  printf("====== END CONCAT ======\n");
}

void test_append_char()
{
  printf("\n====== TEST APPEND CHAR ======\n");

  STRING_ST *str = new_string("Hello Sweetheart", 20);
  printf("str: %s with length: %ld and memlength: %ld\n", get_str_literal(str), get_str_length(str), get_str_memlength(str));
  append_char(str, 'X');
  append_char(str, 'Y');
  append_char(str, 'Z');
  append_char(str, '0');
  printf("str: %s with length: %ld and memlength: %ld\n", get_str_literal(str), get_str_length(str), get_str_memlength(str));
  del_string(str);

  printf("====== END APPEND CHAR ======\n");
}

int main(int argc, char *argv[])
{
  test_append_char();
  test_concat();

  return 0;
}
