#ifndef STRING_ST_H
#define STRING_ST_H

typedef struct string_t STRING_ST;
typedef struct vector_t VECTOR_ST;

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
STRING_ST* str_concat(int n, ...);
STRING_ST* str_copy(STRING_ST *s);
STRING_ST* s_append_c(STRING_ST *dst, char ch);
STRING_ST* s_append_l(STRING_ST *dst, const char *src);

int del_str(STRING_ST *str);
size_t get_str_len(STRING_ST *str);
size_t get_str_mlen(STRING_ST *str);
const char* get_str_l(STRING_ST *str);

#endif /* STRING_ST_H */
