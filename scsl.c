#include "scsl.h"
#include "scsl_internal.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

String string_new_empty(size_t cap) {
  struct string_meta *meta = malloc(META_SIZE + cap);
  if(meta == NULL) return NULL;

  meta->len = 0;
  meta->cap = cap;

  return (String)meta;
}

String string_new_with_capacity(char *s, size_t cap) {
  if(s == NULL) return string_new_empty(cap);

  size_t len = strlen(s);
  cap = len > cap ? len : cap;

  struct string_meta *meta = malloc(META_SIZE + cap);
  if(meta == NULL) return NULL;

  meta->len = len;
  meta->cap = cap;

  memcpy(++meta, s, len);

  return (String)meta;
}

String string_new(char *s) {
  return string_new_with_capacity(s, STRING_INITIAL_CAP);
}

void string_destroy(String s) {
  struct string_meta *meta = META_FROM_STRING(s);

  free(meta);
}

void string_print(String s) {
  for(size_t i = 0; i < string_length(s); i++) {
    putchar(s[i]);
  }
}

size_t string_length(String s) {
  struct string_meta *meta = META_FROM_STRING(s);

  return meta->len;
}

size_t string_capacity(String s) {
  struct string_meta *meta = META_FROM_STRING(s);

  return meta->cap;
}

bool string_equal(String a, String b) {
  struct string_meta *meta_a = META_FROM_STRING(a);
  struct string_meta *meta_b = META_FROM_STRING(b);

  if(meta_a->len != meta_b->len) return false;

  for(size_t i = 0; i < meta_a->len; i++) {
    if(a[i] != b[i]) return false;
  }

  return true;
}

bool string_equal_to_c_string(String s, char *c) {
  struct string_meta *meta_a = META_FROM_STRING(s);

  size_t i;
  for(i = 0; i < meta_a->len; i++) {
    if(c[i] == 0 || s[i] != c[i]) return false;
  }

  return c[i] == 0;
}

String string_clone(String s) {
  return string_clone_with_capacity(s, STRING_INITIAL_CAP);
}

String string_clone_with_capacity(String s, size_t cap) {
  size_t len = string_length(s);
  cap = len > cap ? len : cap;

  String clone = string_new_with_capacity(NULL, cap);
  memcpy(clone, s, len);

  struct string_meta *meta = META_FROM_STRING(clone);
  meta->len = len;

  return clone;
}

void string_grow_capacity(String *s, size_t cap) {
  if(string_capacity(*s) >= cap) return;

  String new = string_clone_with_capacity(*s, cap);
  string_destroy(*s);
  *s = new;
}

void string_copy(String dest, String src) {
  struct string_meta *dest_meta = META_FROM_STRING(dest);
  struct string_meta *src_meta = META_FROM_STRING(src);

  if(dest_meta->cap >= src_meta->len) {
    memcpy(dest, src, src_meta->len);
    dest_meta->len = src_meta->len;
    return;
  }

  /*string_grow_capacity(&dest, src_meta->len);*/

  memcpy(dest, src, src_meta->len);
  dest_meta->len = src_meta->len;
}

String string_concat(String a, String b) {
  size_t len_a = string_length(a);
  size_t len_b = string_length(b);
  String c = string_new_with_capacity(NULL, len_a + len_b);

  struct string_meta *meta = META_FROM_STRING(c);
  meta->len = len_a + len_b;

  memcpy(c, a, len_a);
  memcpy(c + len_a, b, len_b);

  return c;
}

/* trims leading spaces from a string s, changing the original string */
void string_trim_leading(String s);

/* trims trailing spaces from a string s, changing the original string */
void string_trim_trailing(String s);

/* trims leading and trailing spaces from a string s, changing the original string */
void string_trim(String s);
