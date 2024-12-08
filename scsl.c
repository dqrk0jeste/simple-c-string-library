#include <scsl.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

String string_new_empty(size_t cap) {
  struct string_meta *meta = malloc(META_SIZE + cap);
  if(meta == NULL) return NULL;

  meta->len = 0;
  meta->cap = cap;

  return (String)++meta;
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
  size_t len_a = string_length(a);
  size_t len_b = string_length(b);

  if(len_a != len_b) return false;

  for(size_t i = 0; i < len_a; i++) {
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

String string_clone_with_capacity(String s, size_t cap) {
  size_t len = string_length(s);
  cap = len > cap ? len : cap;

  String clone = string_new_with_capacity(NULL, cap);
  memcpy(clone, s, len);

  struct string_meta *meta = META_FROM_STRING(clone);
  meta->len = len;

  return clone;
}

String string_clone(String s) {
  return string_clone_with_capacity(s, STRING_INITIAL_CAP);
}

void string_grow_capacity(String *s, size_t cap) {
  if(string_capacity(*s) >= cap) return;

  String new = string_clone_with_capacity(*s, cap);
  string_destroy(*s);
  *s = new;
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
void string_trim_leading(String s) {
  struct string_meta *meta = META_FROM_STRING(s);
  size_t i = 0;
  while(s[i] == ' ' && i < meta->len) i++;

  size_t initial_len = meta->len;

  meta->len -= i;

  size_t j = 0;
  while(i < initial_len) {
    s[j++] = s[i++];
  }
}

void string_trim_trailing(String s) {
  struct string_meta *meta = META_FROM_STRING(s);
  size_t i = meta->len - 1;
  while(s[i] == ' ' && i >= 0) i--;

  meta->len = i + 1;
}

void string_trim(String s) {
  string_trim_trailing(s);
  string_trim_leading(s);
}

int32_t string_index_of(String s, char c, size_t start) {
  for(size_t i = start; i < string_length(s); i++) {
    if(s[i] == c) return i;
  }

  return -1;
}

int32_t string_index_of_any(String s, char *c, size_t start, char *which) {
  for(size_t i = start; i < string_length(s); i++) {
    char *t = c;
    while(*t != 0) {
      if(s[i] == *t) {
        if(which != NULL) {
          *which = *t;
        }
        return i;
      }
      t++;
    }
  }

  return -1;
}

String string_substring(String s, size_t start, size_t end) {
  size_t len = string_length(s);
  if(end > len) end = len;
  if(start > end) return string_new_empty(0);

  String sub = string_new_with_capacity(NULL, end - start);
  memcpy(sub, s + start, end - start);
  struct string_meta *meta = META_FROM_STRING(sub);
  meta->len = end - start;

  return sub;
}

