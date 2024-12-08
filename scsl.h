#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

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

/* clones the provided string s and returns a new string with capacity cap */
String string_clone_with_capacity(String s, size_t cap);

/* concatinates two strings a and b and returns it as a new allocated string */
String string_concat(String a, String b);

/* trims leading spaces from a string s, changing the original string */
void string_trim_leading(String s);

/* trims trailing spaces from a string s, changing the original string */
void string_trim_trailing(String s);

/* trims leading and trailing spaces from a string s, changing the original string */
void string_trim(String s);

/* find first occurrence of c in string s after start, -1 for no such char in the string */
int32_t string_index_of(String s, char c, size_t start);

/* find any char specified in a c null-terminated string c;
 * returning the index and which char was found in *which pointer; NULL to dismiss */
int32_t string_index_of_any(String s, char *c, size_t start, char *which);

/* returns a new substring starting at start index and until end (not inlcuding end) */
String string_substring(String s, size_t start, size_t end);

