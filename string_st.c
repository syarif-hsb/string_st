#include <stdlib.h>
#include <string.h>
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
int append_char(STRING_ST *string, char ch)
{
  if (!string)
    return STRING_NULL;
  if (!string->p)
    return STRING_CHAR_NULL;

  size_t len = string->length;
  size_t mlen = string->memlength;
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
    return 0;
  return string->length;
}

size_t get_str_memlength(STRING_ST *string)
{
  if (!string)
    return 0;
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

int fill_string(STRING_ST *string, const char *src)
{
  if (!string)
    return 1;

  size_t mlen = string->memlength;

  int n = 0;
  while (src[n] != '\0' && n < mlen)
    n++;

  int i;
  for (i = 0; i < n; i++) {
    string->p[i] = src[i];
  }

  string->length = n;
  string->p[i] = '\0';

  return 0;
}

STRING_ST* new_empty_string_s(size_t sz)
{
  struct string_t *string;
  string = malloc(sizeof(struct string_t));
  if (!string)
    return NULL;

  string->p = calloc(sz, sizeof(sz));
  if (!string->p) {
    free(string);
    return NULL;
  }

  string->length = 0;
  string->memlength = sz;

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

  fill_string(string, s);

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
