#include <scsl.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr) \
  printf("ASSERTION `" #expr "` at line %d ", __LINE__); \
  if(expr) { \
    printf("PASSED\n"); \
  } else { \
    printf("FAILED\n"); \
    exit(1); \
  } \

#define PRINT_TEST_INFO printf("\n--TESTING %s--\n", __FUNCTION__);

void test_string_creation_equality() {
  PRINT_TEST_INFO;
  String a = string_new("this is a string");

  ASSERT(a != NULL);
  ASSERT(string_length(a) == 16);

  ASSERT(string_equal_to_c_string(a, "this is a string"));
  ASSERT(!string_equal_to_c_string(a, "this is a string something"));
  ASSERT(!string_equal_to_c_string(a, "this is a s"));

  String b = string_new_with_capacity("this is another string", 1);

  ASSERT(string_capacity(b) == string_length(b));

  ASSERT(string_equal(a, a));
  ASSERT(string_equal(b, b));
  ASSERT(!string_equal(a, b));

  String c = string_new_with_capacity("string of len 16", 128);

  ASSERT(!string_equal(a, c));
  ASSERT(string_capacity(c) == 128);
  ASSERT(string_length(c) == 16);

  String d = string_new_empty(45);
  ASSERT(string_capacity(d) == 45);

  string_destroy(a);
  string_destroy(b);
  string_destroy(c);
  string_destroy(d);
}

void test_string_cloning() {
  PRINT_TEST_INFO;
  String a = string_new_with_capacity("string to be cloned", 128);
  String b = string_clone_with_capacity(a, 256);

  ASSERT(string_equal(a, b));
  ASSERT(string_capacity(b) == 256);
  ASSERT(string_length(b) == 19);

  String c = string_clone_with_capacity(a, 5);

  ASSERT(string_equal(a, c));
  ASSERT(string_length(c) == 19);
  ASSERT(string_capacity(c) == 19);

  string_destroy(a);
  string_destroy(b);
  string_destroy(c);
}

void test_string_concatination() {
  PRINT_TEST_INFO;
  String foo = string_new("foo");
  String bar = string_new("bar");

  String foobar = string_concat(foo, bar);

  ASSERT(string_length(foobar) == 6);
  ASSERT(string_equal_to_c_string(foobar, "foobar"));

  string_destroy(foo);
  string_destroy(bar);
  string_destroy(foobar);
}

void test_string_growing() {
  PRINT_TEST_INFO;
  String s = string_new_with_capacity("string to be grown", 256);
  ASSERT(string_capacity(s) == 256);

  string_grow_capacity(&s, 64);
  ASSERT(string_capacity(s) == 256);
  ASSERT(string_equal_to_c_string(s, "string to be grown"));

  string_grow_capacity(&s, 512);
  ASSERT(string_capacity(s) == 512);
  ASSERT(string_equal_to_c_string(s, "string to be grown"));

  string_destroy(s);
}

void test_string_trimming() {
  PRINT_TEST_INFO;
  String s = string_new("       string with spaces");
  string_trim_leading(s);

  ASSERT(string_length(s) == 18);
  ASSERT(string_equal_to_c_string(s, "string with spaces"));

  string_destroy(s);

  s = string_new("string with spaces          ");
  string_trim_trailing(s);

  ASSERT(string_length(s) == 18);
  ASSERT(string_equal_to_c_string(s, "string with spaces"));

  s = string_new("               string with spaces          ");
  string_trim(s);

  ASSERT(string_length(s) == 18);
  ASSERT(string_equal_to_c_string(s, "string with spaces"));

  string_destroy(s);

  s = string_new("                ");
  string_trim_leading(s);

  ASSERT(string_length(s) == 0);
  ASSERT(string_equal_to_c_string(s, ""));

  string_destroy(s);

  s = string_new("                ");
  string_trim_trailing(s);

  ASSERT(string_length(s) == 0);
  ASSERT(string_equal_to_c_string(s, ""));

  string_destroy(s);

  s = string_new("                ");
  string_trim(s);

  ASSERT(string_length(s) == 0);
  ASSERT(string_equal_to_c_string(s, ""));

  string_destroy(s);
}

void test_string_index_of() {
  String s = string_new("looking for char k");
  ASSERT(string_index_of(s, 'k', 2) == 3);
  ASSERT(string_index_of(s, 'k', 5) == 17);
  ASSERT(string_index_of(s, 'k', 123) == -1);
  ASSERT(string_index_of(s, 'z', 0) == -1);
}

void test_string_index_of_any() {
  String s = string_new("one, two, three");

  ASSERT(string_index_of(s, ',', 0) == 3);
  ASSERT(string_index_of(s, ',', 4) == 8);
  ASSERT(string_index_of_any(s, "we", 6, NULL) == 6);

  char c;
  ASSERT(string_index_of_any(s, "nr", 0, &c) == 1);
  ASSERT(c == 'n');
}

void test_substrings() {
  String s = string_new("abcdefghijk");
  ASSERT(string_equal_to_c_string(string_substring(s, 9, 5), ""));
  ASSERT(string_equal_to_c_string(string_substring(s, 2, 5), "cde"));
  ASSERT(string_equal(string_substring(s, 0, string_length(s)), s));
  ASSERT(string_equal_to_c_string(string_substring(s, 2, 123), "cdefghijk"));
}

int main(int argc, char *argv[]) {
  printf("\nTESTING...\n");

  test_string_creation_equality();
  test_string_cloning();
  test_string_concatination();
  test_string_growing();
  test_string_trimming();
  test_string_index_of();
  test_string_index_of_any();
  test_substrings();

  printf("\nALL TESTS PASSED\n");
  return 0;
}
