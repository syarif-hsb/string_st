#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_st.h"

void test_concat()
{
  printf("\n====== TEST CONCAT ======\n");

  STRING_ST *str1 = new_string_s("Hello Sweetheart", 20);
  STRING_ST *str2 = new_empty_string_s(256);
  STRING_ST *str3 = new_empty_string();
  STRING_ST *str4 = new_string_s("Hello There", 20);

  STRING_ST *result = concat_str(4, str1, str2, str3, str4);

  printf("Concat result: %s\n", get_str_literal(result));

  del_string(str1);
  del_string(str2);
  del_string(str3);
  del_string(str4);
  del_string(result);

  printf("====== END CONCAT ======\n");
}

void test_append_char()
{
  printf("\n====== TEST APPEND CHAR ======\n");

  STRING_ST *str = new_string_s("Hello Sweetheart", 20);

  printf("str: %s with length: %ld and memlength: %ld\n", get_str_literal(str), get_str_length(str), get_str_memlength(str));

  append_char(str, 'X');
  append_char(str, 'Y');
  append_char(str, 'Z');
  append_char(str, '0');

  printf("str: %s with length: %ld and memlength: %ld\n", get_str_literal(str), get_str_length(str), get_str_memlength(str));

  del_string(str);

  printf("====== END APPEND CHAR ======\n");
}

void test_creation_wo_size()
{
  printf("\n====== TEST CREATION WO SIZE ======\n");

  STRING_ST *str = new_string("This is arbitrary string");
  printf("Str: %s\n", get_str_literal(str));
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_length(str), get_str_memlength(str));
  del_string(str);

  printf("====== END CREATION WO SIZE ======\n");
}

void test_creation()
{
  printf("\n====== TEST CREATION ======\n");

  size_t sz = 5;
  STRING_ST *str = new_string_s("Big enough string", sz);
  printf("Big string with small number of size\n");
  printf("Str: %s, size: %ld\n", get_str_literal(str), sz);
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_length(str), get_str_memlength(str));
  del_string(str);

  printf("====== END CREATION ======\n");
}

void test_non_terminated_creation()
{
  printf("\n====== TEST NON-TERMINATED CREATION ======\n");

  const char *cs = "Hello, World!";
  char *s = malloc(14 * sizeof(char));
  strcpy(s, cs);

  /* This commented line below created memory error */
  /* s[13] = 'A'; */

  size_t sz = 12;
  STRING_ST *str = new_string_s(s, sz);
  printf("Str: %s, size: %ld\n", get_str_literal(str), sz);
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_length(str), get_str_memlength(str));
  del_string(str);
  free(s);

  printf("====== END NON-TERMINATED CREATION ======\n");
}

int main(int argc, char *argv[])
{
  test_creation();
  test_creation_wo_size();
  test_non_terminated_creation();
  test_append_char();
  test_concat();

  return 0;
}
