#pragma once

#include <stddef.h>
#include <stdbool.h>

#ifndef STRING_INITIAL_CAP
  #define STRING_INITIAL_CAP 64
#endif

struct string_meta {
  size_t len;
  size_t cap;
};

#define META_SIZE sizeof(struct string_meta)
#define META_FROM_STRING(s) (struct string_meta *)((s) - META_SIZE)

typedef char* String;

/* initialize a new string with the value of a c null-terminated string s */
String string_new(char *s);

/* creates an empty string with capacity cap */
String string_new_empty(size_t cap);

/* initialize a new string with the value of a c null-terminated string s
 * and minimum capacity of cap */
String string_new_with_capacity(char *s, size_t cap);

/* destroy allocated string */
void string_destroy(String s);

/* prints a string to the stdout */
void string_print(String s);

/* return the length of the provided string s */
size_t string_length(String s);

/* return the internal capacity of the provided String s */
size_t string_capacity(String s);

/* grow this string capacity to cap */
void string_grow_capacity(String *s, size_t cap);

/* check if two provided strings a and b are equal */
bool string_equal(String a, String b);

/* check if the provided string s is the same as a c-string c */
bool string_equal_to_c_string(String s, char *c);

/* clones the provided string s and returns a new string */
String string_clone(String s);

/* copies the provided string src into dest */
void string_copy(String dest, String src);

/* concatinates two strings a and b and returns it as a new allocated string */
String string_concat(String a, String b);

/* trims leading spaces from a string s, changing the original string */
void string_trim_leading(String s);

/* trims trailing spaces from a string s, changing the original string */
void string_trim_trailing(String s);

/* trims leading and trailing spaces from a string s, changing the original string */
void string_trim(String s);
