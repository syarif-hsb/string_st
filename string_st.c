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

/* Initialized Variables */
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

typedef struct vector_t {
  STRING_ST **strings;
  size_t len;
  size_t mlen;
} VECTOR_ST;
/* End of Struct declaration */

/* Function declaration */
VECTOR_ST* parse_delimited(STRING_ST *string, const char *del);
VECTOR_ST* new_vector();
VECTOR_ST* new_vector_s(size_t sz);
VECTOR_ST* v_append_str(VECTOR_ST *dst, STRING_ST *src);
VECTOR_ST* v_concat_vec(int n, ...);
VECTOR_ST* v_copy(VECTOR_ST *src);

int del_vector(VECTOR_ST *v);

STRING_ST* new_empty_string();
STRING_ST* new_empty_string_s(size_t sz);
STRING_ST* new_string(const char *s);
STRING_ST* new_string_s(const char *s, size_t sz);
STRING_ST* concat_str(int n, ...);
STRING_ST* str_copy(STRING_ST *s);

int del_string(STRING_ST *str);
int append_char(STRING_ST *dst, char ch);
int append_str_literal(STRING_ST *dst, const char *src);

const char* get_str_literal(STRING_ST *str);
const char* v_get_str(VECTOR_ST* v, size_t index);
const char* get_str_error(int errnum);
size_t get_str_length(STRING_ST *str);
size_t get_str_memlength(STRING_ST *str);
size_t get_v_length(VECTOR_ST *v);
size_t get_v_memlength(VECTOR_ST *v);
/* End of Function declaration */

/* Functions */
VECTOR_ST* v_concat_vec(int n, ...)
{
  va_list ap, aq;
  va_start(ap, n);
  va_copy(aq, ap);

  size_t total_len = 0;
  for(int i = 0; i < n; i++) {
    VECTOR_ST *tmp = va_arg(ap, VECTOR_ST*);
    if (!tmp)
      continue;
    total_len += tmp->len;
  }
  va_end(ap);

  VECTOR_ST *v;
  v = new_vector_s(total_len);
  if (!v)
    return NULL;

  for (int i = 0; i < n; i++) {
    VECTOR_ST *tmp = va_arg(aq, VECTOR_ST*);
    /* TODO: Make a copy */
    for (int j = 0; j < tmp->len; j++)
      v_append_str(v, tmp->strings[j]);
  }
  va_end(aq);

  return v;
}

VECTOR_ST* v_append_str(VECTOR_ST *dst, STRING_ST *src)
{
  size_t len = dst->len;
  size_t mlen = dst->mlen;

  len += 1;
  if (len > mlen) {
    STRING_ST **tmp = calloc(len + 1, sizeof(STRING_ST*));
    if (!tmp)
      return NULL;

    memcpy(tmp, dst->strings, mlen * sizeof(STRING_ST*));
    mlen = len;
    free(dst->strings);
    dst->strings = tmp;
  }

  dst->strings[len - 1] = str_copy(src);
  dst->len = len;
  dst->mlen = mlen;

  return dst;
}

VECTOR_ST* new_vector()
{
  VECTOR_ST *v;
  v = new_vector_s(DEFAULT_MEMORY_LEN);
  if (!v)
    return NULL;

  return v;
}

VECTOR_ST* new_vector_s(size_t sz)
{
  VECTOR_ST *v;
  v = calloc(1, sizeof(VECTOR_ST));
  if (!v)
    return NULL;
  v->strings = calloc(sz, sizeof(STRING_ST*));
  if (!v->strings) {
    free(v);
    return NULL;
  }

  v->len = 0;
  v->mlen = sz;

  return v;
}

STRING_ST* concat_str(int n, ...)
{
  va_list ap, aq;
  va_start(ap, n);
  va_copy(aq, ap);

  size_t total_len = 0;
  for (int i = 0; i < n; i++) {
    STRING_ST *tmp = va_arg(ap, STRING_ST*);
    if (!tmp)
      continue;
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

STRING_ST* str_copy(STRING_ST *src)
{
  size_t len = src->len;
  size_t mlen = src->mlen;

  STRING_ST *dst;
  dst = new_empty_string_s(mlen);
  if (!dst)
    return NULL;

  memcpy(dst->p, src->p, mlen * sizeof(char));
  dst->len = len;
  dst->mlen = mlen;

  return dst;
}

VECTOR_ST* v_copy(VECTOR_ST *src)
{
  size_t len = src->len;
  size_t mlen = src->mlen;

  VECTOR_ST *dst;
  dst = new_vector_s(mlen);
  if (!dst)
    return NULL;

  for (size_t i = 0; i < len; i++) {
    dst->strings[i] = str_copy(src->strings[i]);
  }

  dst->len = len;
  dst->mlen = mlen;

  return dst;
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
    char *tmp = calloc(mlen + DEFAULT_MEMORY_LEN, sizeof(char));
    if (!tmp)
      return STRING_MEM_ALLOC;

    memcpy(tmp, dst->p, mlen * sizeof(char));
    mlen += DEFAULT_MEMORY_LEN;
    free(dst->p);
    dst->p = tmp;
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
    char *tmp = calloc(len + 1, sizeof(char));
    if (!tmp)
      return STRING_MEM_ALLOC;

    memcpy(tmp, dst->p, mlen * sizeof(char));
    mlen = len + 1;
    free(dst->p);
    dst->p = tmp;
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

  return str->p;
}

const char* v_get_str(VECTOR_ST* v, size_t index)
{
  /* TODO: add guard */
  if (!v)
    return NULL;

  return get_str_literal(v->strings[index]);
}

size_t get_v_length(VECTOR_ST *v)
{
  /* TODO: add guard */
  if (!v)
    return 0;
  return v->len;
}

size_t get_v_memlength(VECTOR_ST *v)
{
  /* TODO: add guard */
  if (!v)
    return 0;
  return v->mlen;
}

STRING_ST* new_empty_string_s(size_t sz)
{
  STRING_ST *str;
  str = calloc(1, sizeof(STRING_ST));
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

int del_vector(VECTOR_ST *v)
{
  /* TODO: Add guard for null pointers */
  for (int i = 0; i < v->len; i++)
    del_string(v->strings[i]);

  free(v->strings);
  free(v);

  return 0;
}

int del_string(STRING_ST *str)
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
