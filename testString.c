/* This file is part of STRING ST.
 *
 * STRING ST is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version
 * 2 of the License, or (at your option) any later version.
 *
 * STRING ST is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with STRING ST.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "string_st.h"

void test_KMP()
{
  printf("\n====== TEST KMP ======\n");
  STRING_ST* s = new_str("ABC ABCDAB ABCDABCDABDE");
  STRING_ST* w = new_str("ABCDABD");

  uint32_t ret = get_case_match(s, w);

  del_str(s);
  del_str(w);

  s = new_str("AbABaBabAB");
  w = new_str("AB");

  ret = get_case_match(s, w);
  printf("Match no ignore case at index %d\n", ret);
  ret = get_icase_match(s, w);
  printf("Match ignore case at index %d\n", ret);

  printf("\n");

  int counter = 0;
  while ((ret = get_case_match(s, w)) != (uint32_t)(-1)) {
    printf("Match no ignore case %d: at index %d\n", counter, ret);
    counter += 1;
  }

  printf("\n");

  while ((ret = get_icase_match(s, w)) != (uint32_t)(-1)) {
    printf("Match ignore case %d: at index %d\n", counter, ret);
    counter += 1;
  }

  del_str(s);
  del_str(w);
  printf("====== END TEST KMP ======\n");
}

void test_transpose()
{
  printf("\n====== TEST TRANSPOSE ======\n");
  TABLE_ST *t = new_table();

  VECTOR_ST *v1 = new_vector();
  STRING_ST *s1 = new_str("a");
  STRING_ST *s2 = new_str("b");
  STRING_ST *s3 = new_str("c");
  STRING_ST *s4 = new_str("c2");
  v_append(v1, s1);
  v_append(v1, s2);
  v_append(v1, s3);
  v_append(v1, s4);

  VECTOR_ST *v2 = new_vector();
  s1 = new_str("d");
  s2 = new_str("e");
  s3 = new_str("f");
  v_append(v2, s1);
  v_append(v2, s2);
  v_append(v2, s3);

  VECTOR_ST *v3 = new_vector();
  s1 = new_str("g");
  s2 = new_str("h");
  s3 = new_str("i");
  v_append(v3, s1);
  v_append(v3, s2);
  v_append(v3, s3);

  t_append(t, v1);
  t_append(t, v2);
  t_append(t, v3);

  printf("Before\n");
  printf("Vector 1: %s,%s,%s,%s\n", t_get_str_l(t, 0, 0), t_get_str_l(t, 0, 1), t_get_str_l(t, 0, 2), t_get_str_l(t, 0, 3));
  printf("Vector 2: %s,%s,%s\n", t_get_str_l(t, 1, 0), t_get_str_l(t, 1, 1), t_get_str_l(t, 1, 2));
  printf("Vector 3: %s,%s,%s\n", t_get_str_l(t, 2, 0), t_get_str_l(t, 2, 1), t_get_str_l(t, 2, 2));
  printf("Max Vector: %u\n", t_get_max_vector_len(t));

  t = transpose(t);
  printf("After\n");
  printf("Vector 1: %s,%s,%s,%s\n", t_get_str_l(t, 0, 0), t_get_str_l(t, 0, 1), t_get_str_l(t, 0, 2), t_get_str_l(t, 0, 3));
  printf("Vector 2: %s,%s,%s\n", t_get_str_l(t, 1, 0), t_get_str_l(t, 1, 1), t_get_str_l(t, 1, 2));
  printf("Vector 3: %s,%s,%s\n", t_get_str_l(t, 2, 0), t_get_str_l(t, 2, 1), t_get_str_l(t, 2, 2));
  printf("Vector 4: %s\n", t_get_str_l(t, 3, 0));
  printf("Max Vector: %u\n", t_get_max_vector_len(t));

  del_table(t);
  printf("====== END TEST TRANSPOSE ======\n");
}

void test_table()
{
  printf("\n====== TEST TABLE ======\n");
  VECTOR_ST *v1 = new_vector();
  STRING_ST *str1 = new_str("Test1");
  STRING_ST *str2 = new_str("Test2");
  STRING_ST *str3 = new_str("Test3");
  v_append(v1, s_copy(str1));
  v_append(v1, s_copy(str2));
  v_append(v1, s_copy(str3));

  const char *s;
  for (int i = 0; i < v_get_len(v1); i++) {
    s = v_get_str_l(v1, i);
    printf("String %d: %s\n", i, s);
  }

  VECTOR_ST *v2 = new_vector();
  STRING_ST *str4 = new_str("Test4");
  STRING_ST *str5 = new_str("Test5");
  STRING_ST *str6 = new_str("Test6");
  v_append(v2, s_copy(str4));
  v_append(v2, s_copy(str5));
  v_append(v2, s_copy(str6));

  VECTOR_ST *v3 = v_concat(2, v1, v2);
  printf("\n");

  for (int i = 0; i < v_get_len(v3); i++) {
    s = v_get_str_l(v3, i);
    printf("String %d: %s\n", i, s);
  }

  TABLE_ST *t = new_table();
  t = t_append(t, v_copy(v1));
  t = t_append(t, v_copy(v2));
  t = t_append(t, v_copy(v3));

  printf("String: %s\n", t_get_str_l(t, 1, 2));

  del_str(str1);
  del_str(str2);
  del_str(str3);
  del_str(str4);
  del_str(str5);
  del_str(str6);
  del_vector(v1);
  del_vector(v2);
  del_vector(v3);
  del_table(t);
  printf("====== END TEST TABLE ======\n");
}

void test_copy()
{
  printf("\n====== TEST COPY ======\n");
  STRING_ST *str1 = new_str("Hai Mega");
  STRING_ST *str2 = s_copy(str1);

  del_str(str1);
  del_str(str2);
  printf("====== END COPY ======\n");
}

void test_parse_delimiter()
{
  printf("\n====== TEST PARSE DELIMITER ======\n");
  STRING_ST *s = new_str("This;is;the ; string;;And the next;;ajsfhkjafn fkajhfkj ahfqrqje hasfkjh kjhke lakf njafq jr3oij aakfhj fhew fhq aj ahf la hfqohr099084lkj hfiu q r hkjdhakjf lhk lhiuoew lhaj hfalflak laj ieqlr q lkh oihowf halhfo a lah sfh  al fjadl fa lafjklhjriojqhiouriqowurqoiwuroi iokyuaidjflkajfklaj lkfjalkjfoiuoiuoijqlkrjih oiqfuoi upoiupoiuv iosudfpouipo iuqpofujqp w;lqn qiuqpiur9u 70sgpiu;");

  printf("String: \"%s\"\n\n", s_get_str_l(s));


  VECTOR_ST *v = parse_delimited_c(s, ';');

  printf("  vector: len: %u, mlen: %u\n", v_get_len(v), v_get_mlen(v));
  for (int i = 0; i < v_get_len(v); i++) {
    printf("Field %d: %s\n", i, v_get_str_l(v, i));
    printf("\tlen: %u, mlen: %u\n", s_get_len(v_get_str(v, i)), s_get_mlen(v_get_str(v, i)));
  }

  del_str(s);
  del_vector(v);

  printf("====== END PARSE DELIMITER ======\n");
}

void test_v_concat()
{
  printf("\n====== TEST CONCAT VECTOR ======\n");
  VECTOR_ST *v1 = new_vector();
  STRING_ST *str1 = new_str("Hai Mega");
  STRING_ST *str2 = new_str("Hai Semua");
  STRING_ST *str3 = new_str("Hello, World!");
  v_append(v1, s_copy(str1));
  v_append(v1, s_copy(str2));
  v_append(v1, s_copy(str3));

  const char *s;
  for (int i = 0; i < v_get_len(v1); i++) {
    s = v_get_str_l(v1, i);
    printf("String %d: %s\n", i, s);
  }

  VECTOR_ST *v2 = new_vector();
  STRING_ST *str4 = new_str("Hai Kamu");
  STRING_ST *str5 = new_str("Hai Ho");
  STRING_ST *str6 = new_str("Hello, Space!");
  v_append(v2, s_copy(str4));
  v_append(v2, s_copy(str5));
  v_append(v2, s_copy(str6));

  VECTOR_ST *v3 = v_concat(2, v1, v2);
  printf("\n");

  for (int i = 0; i < v_get_len(v3); i++) {
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

  printf("Concat result: %s\n", s_get_str_l(result));
  printf("Str Length: %u, Str Memory Length: %u\n",
      s_get_len(result), s_get_mlen(result));

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

  printf("str: %s with length: %u and memlength: %u\n", s_get_str_l(str), s_get_len(str), s_get_mlen(str));

  s_append_c(str, 'X');
  s_append_c(str, 'Y');
  s_append_c(str, 'Z');
  s_append_c(str, '0');

  printf("str: %s with length: %u and memlength: %u\n", s_get_str_l(str), s_get_len(str), s_get_mlen(str));

  del_str(str);

  printf("====== END APPEND CHAR ======\n");
}

void test_creation_wo_size()
{
  printf("\n====== TEST CREATION WO SIZE ======\n");

  STRING_ST *str = new_str("This is arbitrary string");
  printf("Str: %s\n", s_get_str_l(str));
  printf("Str Length: %u, Str Memory Length: %u\n",
      s_get_len(str), s_get_mlen(str));
  del_str(str);

  printf("====== END CREATION WO SIZE ======\n");
}

void test_creation()
{
  printf("\n====== TEST CREATION ======\n");

  uint32_t sz = 5;
  STRING_ST *str = new_str_s("Big enough string", sz);
  printf("Big string with small number of size\n");
  printf("Str: %s, size: %u\n", s_get_str_l(str), sz);
  printf("Str Length: %u, Str Memory Length: %u\n",
      s_get_len(str), s_get_mlen(str));
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

  uint32_t sz = 12;
  STRING_ST *str = new_str_s(s, sz);
  printf("Str: %s, size: %d\n", s_get_str_l(str), sz);
  printf("Str Length: %u, Str Memory Length: %u\n",
      s_get_len(str), s_get_mlen(str));
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
  test_v_concat();
  test_copy();
  test_parse_delimiter();
  test_table();
  test_transpose();
  test_KMP();

  return 0;
}
