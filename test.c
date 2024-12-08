#include "scsl.h"
#include "scsl_internal.h"

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

  ASSERT(string_capacity(b) >= string_length(b));

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
  ASSERT(string_capacity(c) >= string_length(c));

  string_destroy(a);
  string_destroy(b);
  string_destroy(c);
}

void test_string_concatination() {
  PRINT_TEST_INFO;
  String foo = string_new("foo");
  String bar = string_new("bar");

  String foobar = string_concat(foo, bar);

  ASSERT(string_equal_to_c_string(foobar, "foobar"));
  ASSERT(string_length(foobar) == 6);

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

void test_string_copying() {
  PRINT_TEST_INFO;
  String src = string_new("string to be copied");
  String dest = string_new(NULL);

  string_copy(dest, src);

  ASSERT(string_length(dest) == string_length(src));
  ASSERT(string_capacity(dest) >= string_length(dest));
  ASSERT(string_equal(src, dest));

  string_destroy(src);
  string_destroy(dest);

  String src2 = string_new("wow, string to be copied again");
  String dest2 = string_new_with_capacity("", 10);

  string_copy(dest2, src2);

  string_print(dest2);
  putchar('\n');
  
  ASSERT(string_length(dest2) == string_length(src2));
  /*ASSERT(string_capacity(dest2) >= string_length(dest2));*/
  ASSERT(string_equal(src2, dest2));

  string_destroy(src2);
  string_destroy(dest2);
}

int main(int argc, char *argv[]) {
  printf("\nTESTING...\n");

  test_string_creation_equality();
  /*test_string_cloning();*/
  /*test_string_concatination();*/
  /*test_string_growing();*/
  /*test_string_copying();*/

  printf("\nALL TESTS PASSED\n");
  return 0;
}
