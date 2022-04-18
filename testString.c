#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_st.h"

void v_test_concat()
{
  printf("\n====== TEST CONCAT VECTOR ======\n");
  VECTOR_ST *v1 = new_vector();
  STRING_ST *str1 = new_str("Hai Mega");
  STRING_ST *str2 = new_str("Hai Semua");
  STRING_ST *str3 = new_str("Hello, World!");
  v_append(v1, str1);
  v_append(v1, str2);
  v_append(v1, str3);

  const char *s;
  for (int i = 0; i < get_v_len(v1); i++) {
    s = v_get_str_l(v1, i);
    printf("String %d: %s\n", i, s);
  }

  VECTOR_ST *v2 = new_vector();
  STRING_ST *str4 = new_str("Hai Kamu");
  STRING_ST *str5 = new_str("Hai Ho");
  STRING_ST *str6 = new_str("Hello, Space!");
  v_append(v2, str4);
  v_append(v2, str5);
  v_append(v2, str6);

  VECTOR_ST *v3 = v_concat(2, v1, v2);
  printf("\n");

  for (int i = 0; i < get_v_len(v3); i++) {
    s = v_get_str_l(v3, i);
    printf("String %d: %s\n", i, s);
  }

  del_str(str1);
  del_str(str2);
  del_str(str3);
  del_str(str4);
  del_str(str5);
  del_str(str6);
  del_vector(v1);
  del_vector(v2);
  del_vector(v3);
  printf("====== END CONCAT VECTOR ======\n");
}

void test_concat()
{
  printf("\n====== TEST CONCAT ======\n");

  STRING_ST *str1 = new_str_s("Hello Sweetheart", 8);
  STRING_ST *str2 = new_empty_str_s(256);
  STRING_ST *str3 = new_empty_str();
  STRING_ST *str4 = new_str_s("Hello There", 10);

  STRING_ST *result = s_concat(4, str1, str2, str3, str4);

  printf("Concat result: %s\n", get_str_l(result));
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_len(result), get_str_mlen(result));

  del_str(str1);
  del_str(str2);
  del_str(str3);
  del_str(str4);
  del_str(result);

  printf("====== END CONCAT ======\n");
}

void test_append_char()
{
  printf("\n====== TEST APPEND CHAR ======\n");

  STRING_ST *str = new_str_s("Hello Sweetheart", 20);

  printf("str: %s with length: %ld and memlength: %ld\n", get_str_l(str), get_str_len(str), get_str_mlen(str));

  s_append_c(str, 'X');
  s_append_c(str, 'Y');
  s_append_c(str, 'Z');
  s_append_c(str, '0');

  printf("str: %s with length: %ld and memlength: %ld\n", get_str_l(str), get_str_len(str), get_str_mlen(str));

  del_str(str);

  printf("====== END APPEND CHAR ======\n");
}

void test_creation_wo_size()
{
  printf("\n====== TEST CREATION WO SIZE ======\n");

  STRING_ST *str = new_str("This is arbitrary string");
  printf("Str: %s\n", get_str_l(str));
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_len(str), get_str_mlen(str));
  del_str(str);

  printf("====== END CREATION WO SIZE ======\n");
}

void test_creation()
{
  printf("\n====== TEST CREATION ======\n");

  size_t sz = 5;
  STRING_ST *str = new_str_s("Big enough string", sz);
  printf("Big string with small number of size\n");
  printf("Str: %s, size: %ld\n", get_str_l(str), sz);
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_len(str), get_str_mlen(str));
  del_str(str);

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
  STRING_ST *str = new_str_s(s, sz);
  printf("Str: %s, size: %ld\n", get_str_l(str), sz);
  printf("Str Length: %ld, Str Memory Length: %ld\n", 
      get_str_len(str), get_str_mlen(str));
  del_str(str);
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
  v_test_concat();

  return 0;
}
