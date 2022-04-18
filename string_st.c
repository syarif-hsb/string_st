#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/* Macros */
#define DEFAULT_MEMORY_LEN 256
#define STRING_SUCCESS       0
#define STRING_FAILURE      -1

/* Struct declaration */
typedef struct string_t {
  char *l;
  size_t len;
  size_t mlen;
} STRING_ST;

typedef struct vector_t {
 STRING_ST **strs;
  size_t len;
  size_t mlen;
} VECTOR_ST;
/* End of Struct declaration */

/* Function declaration */
VECTOR_ST* new_vector();
VECTOR_ST* new_vector_s(size_t sz);
VECTOR_ST* v_append(VECTOR_ST *dst, STRING_ST *src);
VECTOR_ST* v_concat(int n, ...);
VECTOR_ST* v_copy(VECTOR_ST *src);
VECTOR_ST* parse_delimited(STRING_ST *string, const char *del);

int del_vector(VECTOR_ST *v);
size_t get_v_len(VECTOR_ST *v);
size_t get_v_mlen(VECTOR_ST *v);
const char* v_get_str_l(VECTOR_ST* v, size_t index);

STRING_ST* new_str(const char *s);
STRING_ST* new_str_s(const char *s, size_t sz);
STRING_ST* new_empty_str();
STRING_ST* new_empty_str_s(size_t sz);
STRING_ST* s_append_c(STRING_ST *dst, char ch);
STRING_ST* s_append_l(STRING_ST *dst, const char *src);
STRING_ST* s_concat(int n, ...);
STRING_ST* s_copy(STRING_ST *s);

int del_str(STRING_ST *str);
size_t get_str_len(STRING_ST *str);
size_t get_str_mlen(STRING_ST *str);
const char* get_str_l(STRING_ST *str);
/* End of Function declaration */

/* Functions */
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
  v->strs = calloc(sz, sizeof(STRING_ST*));
  if (!v->strs) {
    free(v);
    return NULL;
  }

  v->len = 0;
  v->mlen = sz;

  return v;
}

VECTOR_ST* v_append(VECTOR_ST *dst, STRING_ST *src)
{
  size_t len = dst->len;
  size_t mlen = dst->mlen;

  len += 1;
  if (len > mlen) {
    STRING_ST **tmp = calloc(len + 1, sizeof(STRING_ST*));
    if (!tmp)
      return NULL;

    memcpy(tmp, dst->strs, mlen * sizeof(STRING_ST*));
    mlen = len;
    free(dst->strs);
    dst->strs = tmp;
  }

  dst->strs[len - 1] = s_copy(src);
  dst->len = len;
  dst->mlen = mlen;

  return dst;
}

VECTOR_ST* v_concat(int n, ...)
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
    for (int j = 0; j < tmp->len; j++)
      v_append(v, tmp->strs[j]);
  }
  va_end(aq);

  return v;
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
    dst->strs[i] = s_copy(src->strs[i]);
  }

  dst->len = len;
  dst->mlen = mlen;

  return dst;
}

int del_vector(VECTOR_ST *v)
{
  if (!v)
    return STRING_FAILURE;
  if (!v->strs)
    return STRING_FAILURE;

  for (int i = 0; i < v->len; i++) {
    if (!v->strs[i])
      continue;
    del_str(v->strs[i]);
  }

  free(v->strs);
  free(v);

  return STRING_SUCCESS;
}

size_t get_v_len(VECTOR_ST *v)
{
  if (!v)
    return STRING_FAILURE;

  return v->len;
}

size_t get_v_mlen(VECTOR_ST *v)
{
  if (!v)
    return STRING_FAILURE;

  return v->mlen;
}

const char* v_get_str_l(VECTOR_ST* v, size_t index)
{
  if (!v)
    return NULL;
  if (!v->strs)
    return NULL;
  if (!v->strs[index])
    return NULL;

  return get_str_l(v->strs[index]);
}

STRING_ST* new_str(const char *s)
{
  STRING_ST *str = new_empty_str();
  if (!str)
    return NULL;

  s_append_l(str, s);

  return str;
}

STRING_ST* new_str_s(const char *s, size_t str_len)
{
  STRING_ST *str = new_empty_str_s(str_len + 1);
  if (!str)
    return NULL;

  s_append_l(str, s);

  return str;
}

STRING_ST* new_empty_str()
{
  STRING_ST *str = new_empty_str_s(DEFAULT_MEMORY_LEN);
  if (!str)
    return NULL;

  return str;
}

STRING_ST* new_empty_str_s(size_t sz)
{
  STRING_ST *str;
  str = calloc(1, sizeof(STRING_ST));
  if (!str)
    return NULL;

  str->l = calloc(sz, sizeof(sz));
  if (!str->l) {
    free(str);
    return NULL;
  }

  str->len = 0;
  str->mlen = sz;

  return str;
}

STRING_ST* s_append_c(STRING_ST *dst, char ch)
{
  if (!dst)
    return NULL;
  if (!dst->l)
    return NULL;

  size_t len = dst->len;
  size_t mlen = dst->mlen;

  /* string is full */
  if (len == (mlen - 1)) {
    char *tmp = calloc(mlen + DEFAULT_MEMORY_LEN, sizeof(char));
    if (!tmp)
      return NULL;

    memcpy(tmp, dst->l, mlen * sizeof(char));
    mlen += DEFAULT_MEMORY_LEN;
    free(dst->l);
    dst->l = tmp;
  }

  dst->l[len] = ch;
  dst->l[len + 1] = '\0';

  dst->len= len + 1;
  dst->mlen = mlen;

  return dst;
}

STRING_ST* s_append_l(STRING_ST *dst, const char *src)
{
  if (!dst)
    return NULL;
  if (!dst->l)
    return NULL;

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
      return NULL;

    memcpy(tmp, dst->l, mlen * sizeof(char));
    mlen = len + 1;
    free(dst->l);
    dst->l = tmp;
  }

  size_t i;
  for (i = 0; i < n; i++) {
    dst->l[i + olen] = src[i];
  }
  dst->l[len] = '\0';

  dst->len = len;
  dst->mlen = mlen;

  return dst;
}

STRING_ST* s_concat(int n, ...)
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
  new_str = new_empty_str_s(total_len);

  for (int i = 0; i < n; i++) {
    STRING_ST *tmp = va_arg(aq, STRING_ST*);
    if (tmp && tmp->l)
      s_append_l(new_str, tmp->l);
  }
  va_end(aq);

  return new_str;
}

STRING_ST* s_copy(STRING_ST *src)
{
  size_t len = src->len;
  size_t mlen = src->mlen;

  STRING_ST *dst;
  dst = new_empty_str_s(mlen);
  if (!dst)
    return NULL;

  memcpy(dst->l, src->l, mlen * sizeof(char));
  dst->len = len;
  dst->mlen = mlen;

  return dst;
}

int del_str(STRING_ST *str)
{
  if (!str->l)
    return STRING_FAILURE;
  free(str->l);

  if (!str)
    return STRING_FAILURE;
  free(str);

  return STRING_SUCCESS;
}

size_t get_str_len(STRING_ST *str)
{
  if (!str)
    return STRING_FAILURE;
  return str->len;
}

size_t get_str_mlen(STRING_ST *str)
{
  if (!str)
    return STRING_FAILURE;
  return str->mlen;
}

const char* get_str_l(STRING_ST *str)
{
  if (!str)
    return NULL;
  if (!str->l)
    return NULL;

  return str->l;
}


