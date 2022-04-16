#ifndef STRING_ST_H
#define STRING_ST_H

#define STRING_SUCCESS   0
#define STRING_NULL      (-1)
#define STRING_CHAR_NULL (-2)
#define STRING_MEM_ALLOC (-3)

#define DEFAULT_MEMORY_LEN 256

typedef struct string_t STRING_ST;

STRING_ST* new_empty_string();
STRING_ST* new_empty_string_s(size_t sz);
STRING_ST* new_string(const char *s, size_t sz);
int del_string(struct string_t *string);

int append_char(STRING_ST *string, char ch);
int append_str_literal(STRING_ST *string, const char *src);
STRING_ST* concat_str(int n, ...);
STRING_ST* concat_str_test(int n, ...);

const char* get_str_literal(STRING_ST *string);
const char* get_str_error(int errnum);
size_t get_str_length(STRING_ST *string);
size_t get_str_memlength(STRING_ST *string);

#endif /* STRING_ST_H */
