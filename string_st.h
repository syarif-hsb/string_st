#ifndef STRING_ST_H
#define STRING_ST_H

typedef struct string_t STRING_ST;
typedef struct vector_t VECTOR_ST;

VECTOR_ST* parse_delimited(STRING_ST *string, const char *del);
VECTOR_ST* new_vector();
VECTOR_ST* new_vector_s(size_t sz);
VECTOR_ST* v_append_str(VECTOR_ST *dst, STRING_ST *src);
VECTOR_ST* v_concat_vec(int n, ...);
int del_vector(VECTOR_ST *v);

STRING_ST* new_empty_string();
STRING_ST* new_empty_string_s(size_t sz);
STRING_ST* new_string(const char *s);
STRING_ST* new_string_s(const char *s, size_t sz);
int del_string(struct string_t *string);

int append_char(STRING_ST *string, char ch);
int append_str_literal(STRING_ST *string, const char *src);
STRING_ST* concat_str(int n, ...);

const char* get_str_literal(STRING_ST *string);
const char* get_str_error(int errnum);
const char* v_get_str(VECTOR_ST* v, size_t index);
size_t get_str_length(STRING_ST *string);
size_t get_str_memlength(STRING_ST *string);
size_t get_v_length(VECTOR_ST *v);
size_t get_v_memlength(VECTOR_ST *v);

#endif /* STRING_ST_H */
