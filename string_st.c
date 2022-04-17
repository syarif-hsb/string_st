#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/* Macros */
#define DEFAULT_MEMORY_LEN 256
#define STRING_SUCCESS     0
#define STRING_NULL       (-1)
#define STRING_ARRAY_NULL (-2)
#define STRING_CHAR_NULL  (-3)
#define STRING_MEM_ALLOC  (-4)

const char *string_null_error = "String is null";
const char *string_array_null_error = "String array is null";
const char *string_char_null_error = "String char pointer is null";
const char *string_not_error = "No error";
const char *string_mem_alloc = "Memory allocation failed";
const char *err_not_found = "No associated error code";

/* Struct declaration */
typedef struct string_t {
  char *p;
  size_t len;
  size_t mlen;
} STRING_ST;

/* Function declaration */
STRING_ST* new_empty_string();
STRING_ST* new_empty_string_s(size_t sz);
STRING_ST* new_string(const char *s);
STRING_ST* new_string_s(const char *s, size_t sz);
int del_string(struct string_t *str);

int append_char(STRING_ST *str, char ch);
int append_str_literal(STRING_ST *str, const char *src);
STRING_ST* concat_str(int n, ...);

const char* get_str_literal(STRING_ST *str);
const char* get_str_error(int errnum);
size_t get_str_length(STRING_ST *str);
size_t get_str_memlength(STRING_ST *str);

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
      total_len += tmp->len;
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

int append_char(STRING_ST *dst, char ch)
{
  if (!dst)
    return STRING_NULL;
  if (!dst->p)
    return STRING_CHAR_NULL;

  size_t len = dst->len;
  size_t mlen = dst->mlen;

  /* string is full */
  if (len == (mlen - 1)) {
    char *ptr = calloc(mlen + DEFAULT_MEMORY_LEN, sizeof(char));
    if (!ptr)
      return STRING_MEM_ALLOC;

    memcpy(ptr, dst->p, mlen);
    mlen += DEFAULT_MEMORY_LEN;
    free(dst->p);
    dst->p = ptr;
  }

  dst->p[len] = ch;
  dst->p[len + 1] = '\0';

  dst->len= len + 1;
  dst->mlen = mlen;

  return STRING_SUCCESS;
}

int append_str_literal(STRING_ST *dst, const char *src)
{
  if (!dst)
    return STRING_NULL;
  if (!dst->p)
    return STRING_CHAR_NULL;

  size_t len = dst->len;
  size_t mlen = dst->mlen;

  size_t n = 0;
  while (src[n] != '\0')
    n++;
  size_t olen = len;
  len += n;

  /* new string exceeds current memory */
  if (len >= mlen) {
    char *ptr = calloc(len + 1, sizeof(char));
    if (!ptr)
      return STRING_MEM_ALLOC;

    memcpy(ptr, dst->p, mlen);
    mlen = len + 1;
    free(dst->p);
    dst->p = ptr;
  }

  size_t i;
  for (i = 0; i < n; i++) {
    dst->p[i + olen] = src[i];
  }
  dst->p[len] = '\0';

  dst->len = len;
  dst->mlen = mlen;

  return STRING_SUCCESS;
}

size_t get_str_length(STRING_ST *str)
{
  if (!str)
    return STRING_NULL;
  return str->len;
}

size_t get_str_memlength(STRING_ST *str)
{
  if (!str)
    return STRING_NULL;
  return str->mlen;
}

const char* get_str_literal(STRING_ST *str)
{
  if (!str)
    return string_null_error;
  if (!str->p)
    return string_char_null_error;

  return (str->p);
}

STRING_ST* new_empty_string_s(size_t sz)
{
  STRING_ST *str;
  str = malloc(sizeof(struct string_t));
  if (!str)
    return NULL;

  str->p = calloc(sz, sizeof(sz));
  if (!str->p) {
    free(str);
    return NULL;
  }

  str->len = 0;
  str->mlen = sz;

  return str;
}

STRING_ST* new_empty_string()
{
  STRING_ST *str = new_empty_string_s(DEFAULT_MEMORY_LEN);
  if (!str)
    return NULL;

  return str;
}

STRING_ST* new_string_s(const char *s, size_t str_len)
{
  STRING_ST *str = new_empty_string_s(str_len + 1);
  if (!str)
    return NULL;

  append_str_literal(str, s);

  return str;
}

STRING_ST* new_string(const char *s)
{
  STRING_ST *str = new_empty_string();
  if (!str)
    return NULL;

  append_str_literal(str, s);

  return str;
}

int del_string(struct string_t *str)
{
  if (!str->p)
    return STRING_CHAR_NULL;
  free(str->p);

  if (!str)
    return STRING_NULL;
  free(str);

  return 0;
}

const char* get_str_error(int errnum)
{
  switch (errnum) {
    case STRING_SUCCESS:
      return string_not_error;
    case STRING_NULL:
      return string_null_error;
    case STRING_ARRAY_NULL:
      return string_array_null_error;
    case STRING_CHAR_NULL:
      return string_char_null_error;
    case STRING_MEM_ALLOC:
      return string_mem_alloc;
    default:
  }
  return err_not_found;
}
