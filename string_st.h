#ifndef STRING_ST_H
#define STRING_ST_H

typedef struct string_t STRING_ST;
typedef struct vector_t VECTOR_ST;

VECTOR_ST* new_vector();
VECTOR_ST* new_vector_s(size_t sz);
VECTOR_ST* v_append(VECTOR_ST *dst, STRING_ST *src);
VECTOR_ST* v_concat(int n, ...);
VECTOR_ST* v_copy(VECTOR_ST *src);
VECTOR_ST* parse_delimited_c(STRING_ST *s, char d);
VECTOR_ST* parse_delimited_l(STRING_ST *s, const char *d);


int del_vector(VECTOR_ST *v);
size_t v_get_len(VECTOR_ST *v);
size_t v_get_mlen(VECTOR_ST *v);
const char* v_get_str_l(VECTOR_ST* v, size_t index);
STRING_ST* v_get_str(VECTOR_ST *v, size_t index);

STRING_ST* new_str(const char *l);
STRING_ST* new_str_s(const char *l, size_t sz);
STRING_ST* new_empty_str();
STRING_ST* new_empty_str_s(size_t sz);
STRING_ST* s_append_c(STRING_ST *dst, char ch);
STRING_ST* s_append_l(STRING_ST *dst, const char *src);
STRING_ST* s_concat(int n, ...);
STRING_ST* s_copy(STRING_ST *s);

int del_str(STRING_ST *s);
size_t s_get_len(STRING_ST *s);
size_t s_get_mlen(STRING_ST *s);
const char* s_get_str_l(STRING_ST *s);

#endif /* STRING_ST_H */
