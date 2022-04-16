#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "string_st.h"

const char *string_null_error = "String is null";
const char *string_char_null_error = "String char pointer is null";
const char *string_not_error = "No error";
const char *string_mem_alloc = "Memory allocation failed";
const char *err_not_found = "No associated error code";

/* Struct declaration */
typedef struct string_t {
  char *p;
  size_t length;
  size_t memlength;
} STRING_ST;

/* Functions */
STRING_ST* concat_str(int n, ...)
{
  va_list ap, aq;
  va_start(ap, n);
  va_copy(aq, ap);

  size_t total_len = 0;
  for (int i = 0; i < n; i++) {
    STRING_ST *tmp = va_arg(ap, STRING_ST*);
    if (tmp)
      total_len += tmp->length;
  }
  va_end(ap);

  STRING_ST *new_str;
  new_str = new_empty_string_s(total_len);

  for (int i = 0; i < n; i++) {
    STRING_ST *tmp = va_arg(aq, STRING_ST*);
    if (tmp && tmp->p)
      append_str_literal(new_str, tmp->p);
  }

  va_end(aq);
  return new_str;
}

STRING_ST* concat_str_test(int n, ...)
{
  va_list ap, aq;
  va_start(ap, n);
  va_copy(aq, ap);

  size_t total_len = 0;
  size_t total_len2 = 0;
  for (int i = 0; i < n; i++) {
    total_len += va_arg(ap, STRING_ST*)->length;
  }

  for (int i = 0; i < n; i++) {
    total_len2 += va_arg(aq, STRING_ST*)->length;
  }

  printf("Total Length: %ld\n", total_len);
  printf("Total Length 2: %ld\n", total_len2);
  va_end(ap);
  va_end(aq);
  return NULL;
}

int append_char(STRING_ST *string, char ch)
{
  if (!string)
    return STRING_NULL;
  if (!string->p)
    return STRING_CHAR_NULL;

  size_t len = string->length;
  size_t mlen = string->memlength;

  /* string is full */
  if (len == (mlen - 1)) {
    mlen += DEFAULT_MEMORY_LEN;
    char *ptr = calloc(mlen, sizeof(char));
    if (!ptr)
      return STRING_MEM_ALLOC;

    memcpy(ptr, string->p, mlen);
    free(string->p);
    string->p = ptr;
  }

  string->p[len] = ch;
  string->p[len + 1] = '\0';

  string->length = len + 1;
  string->memlength = mlen;

  return STRING_SUCCESS;
}

size_t get_str_length(STRING_ST *string)
{
  if (!string)
    return STRING_NULL;
  return string->length;
}

size_t get_str_memlength(STRING_ST *string)
{
  if (!string)
    return STRING_NULL;
  return string->memlength;
}

const char* get_str_literal(STRING_ST *string)
{
  if (!string)
    return string_null_error;
  if (!string->p)
    return string_char_null_error;

  return (string->p);
}

int append_str_literal(STRING_ST *string, const char *src)
{
  if (!string)
    return STRING_NULL;
  if (!string->p)
    return STRING_CHAR_NULL;

  size_t len = string->length;
  size_t mlen = string->memlength;

  size_t n = 0;
  while (src[n] != '\0' && n < DEFAULT_MEMORY_LEN)
    n++;

  /* new string exceeds current memory */
  if (n + len > mlen) {
    mlen = n + len + 1;

    char *ptr = calloc(mlen, sizeof(char));
    if (!ptr)
      return STRING_MEM_ALLOC;

    memcpy(ptr, string->p, mlen);
    free(string->p);
    string->p = ptr;
  }

  size_t i;
  for (i = 0; i < n + len; i++) {
    string->p[i + len] = src[i];
  }


  string->length = n + len;
  string->p[i + len] = '\0';

  return STRING_SUCCESS;
}

/* STRING_ST* concat_str(STRING_ST *x, STRING_ST *y) */
/* { */
/*   if (!x || !y || !x->p || !y->p) */
/*     return NULL; */
/* } */

/* int append_str_literal(STRING_ST *string, const char *src) */
/* { */
/*   if (!string) */
/*     return STRING_NULL; */
/*   if (!string->p) */
/*     return STRING_CHAR_NULL; */

/*   size_t len = string->length; */
/*   size_t mlen = string->memlength; */

/*   size_t n = 0; */
/*   while (src[n] != '\0' && (n + len) < mlen - 1) */
/*     n++; */

/*   size_t i; */
/*   for (i = 0; i < n; i++) { */
/*     string->p[i + len] = src[i]; */
/*   } */

/*   printf("n = %ld, i = %ld, len = %ld, mlen = %ld\n", n, i, len, mlen); */

/*   string->length = n + len; */
/*   string->p[i + len] = '\0'; */

/*   return STRING_SUCCESS; */
/* } */

STRING_ST* new_empty_string_s(size_t sz)
{
  struct string_t *string;
  string = malloc(sizeof(struct string_t));
  if (!string)
    return NULL;

  string->p = calloc(sz + 1, sizeof(sz));
  if (!string->p) {
    free(string);
    return NULL;
  }

  string->length = 0;
  string->memlength = sz + 1;

  return string;
}

STRING_ST* new_empty_string()
{
  STRING_ST *string = new_empty_string_s(DEFAULT_MEMORY_LEN);
  if (!string)
    return NULL;

  return string;
}

STRING_ST* new_string(const char *s, size_t sz)
{
  STRING_ST *string = new_empty_string_s(sz);
  if (!string)
    return NULL;

  append_str_literal(string, s);

  return string;
}

int del_string(struct string_t *string)
{
  if (!string->p)
    return STRING_CHAR_NULL;
  free(string->p);

  if (!string)
    return STRING_NULL;
  free(string);

  return 0;
}

const char* get_str_error(int errnum)
{
  switch (errnum) {
    case STRING_SUCCESS:
      return string_not_error;
    case STRING_NULL:
      return string_null_error;
    case STRING_CHAR_NULL:
      return string_char_null_error;
    case STRING_MEM_ALLOC:
      return string_mem_alloc;
    default:
  }
  return err_not_found;
}
