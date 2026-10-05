#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mergesort.c"

int* A;
int* B;
int cutoff;

void merge_test(const char* test_case_name, int* input_array,
                int* expected_array, int array_size, int leftstart, int leftend,
                int rightstart, int rightend) {
  A = (int*)malloc(sizeof(int) * array_size);
  B = (int*)malloc(sizeof(int) * array_size);

  memcpy(A, input_array, sizeof(int) * array_size);

  merge(leftstart, leftend, rightstart, rightend);

  if (memcmp(A, expected_array, sizeof(int) * array_size) == 0) {
    printf("PASS: %s\n", test_case_name);
  } else {
    printf("FAIL: %s\n", test_case_name);
    if (array_size <= 20) {
      printf("  expected:");
      for (int i = 0; i < array_size; i++) printf(" %d", expected_array[i]);
      printf("\n  got:     ");
      for (int i = 0; i < array_size; i++) printf(" %d", A[i]);
      printf("\n");
    }
  }
  free(A);
  free(B);
}

int main(void) {
  /*Test Cases*/
  int d1[] = {3, 7, 9, 2, 5, 8};
  int e1[] = {2, 3, 5, 7, 8, 9};
  merge_test("basic", d1, e1, 6, 0, 2, 3, 5);

  int d2[] = {1, 9, 2, 3};
  int e2[] = {1, 2, 3, 9};
  merge_test("loop bound", d2, e2, 4, 0, 1, 2, 3);

  int d3[] = {5, 6, 1, 2};
  int e3[] = {1, 2, 5, 6};
  merge_test("right side all smaller", d3, e3, 4, 0, 1, 2, 3);

  int d4[] = {1, 2, 5, 6};
  int e4[] = {1, 2, 5, 6};
  merge_test("already sorted", d4, e4, 4, 0, 1, 2, 3);

  int d5[] = {1, 3, 3, 5, 3, 3, 4, 6};
  int e5[] = {1, 3, 3, 3, 3, 4, 5, 6};
  merge_test("duplicates", d5, e5, 8, 0, 3, 4, 7);

  int d6[] = {2, 1};
  int e6[] = {1, 2};
  merge_test("one element each side", d6, e6, 2, 0, 0, 1, 1);

  int d7[] = {9, 9, 4, 8, 1, 6, 9, 9};
  int e7[] = {9, 9, 1, 4, 6, 8, 9, 9};
  merge_test("middle of array", d7, e7, 8, 2, 3, 4, 5);

  return 0;
}