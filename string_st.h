#ifndef STRING_ST_H
#define STRING_ST_H

#define STRING_SUCCESS   0
#define STRING_NULL      (-1)
#define STRING_CHAR_NULL (-2)
#define STRING_MEM_ALLOC (-3)

#define DEFAULT_MEMORY_LEN 256

typedef struct string_t STRING_ST;

const char* get_str_literal(STRING_ST *string);
const char* get_str_error(int errnum);
int append_char(STRING_ST *string, char ch);
size_t get_str_length(STRING_ST *string);
size_t get_str_memlength(STRING_ST *string);
STRING_ST* new_empty_string();
STRING_ST* new_empty_string_s(size_t sz);
STRING_ST* new_string(const char *s, size_t sz);
int fill_string(STRING_ST *string, const char *src);

#endif /* STRING_ST_H */
