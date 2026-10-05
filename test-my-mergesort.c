#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mergesort.c"

int* A;
int* B;
int cutoff;

int compare_ints(const void* a, const void* b) {
  int x = *(const int*)a;
  int y = *(const int*)b;
  return (x > y) - (x < y);
}

void my_mergesort_test(const char* test_case_name, int* input_array,
                       int array_size) {
  int* expected_array = malloc(array_size * sizeof(int));
  memcpy(expected_array, input_array, array_size * sizeof(int));
  qsort(expected_array, array_size, sizeof(int),
        compare_ints);  // Use inbuilt qsort function for sorting

  A = (int*)malloc(sizeof(int) * array_size);
  B = (int*)malloc(sizeof(int) * array_size);
  memcpy(A, input_array, array_size * sizeof(int));

  my_mergesort(0, array_size - 1);

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

  free(expected_array);
  free(A);
  free(B);
}

/* Builds an array of n random numbers and tests it. */
void run_random_test(const char* test_case_name, int array_size) {
  int* input_array = malloc(sizeof(int) * array_size);
  for (int i = 0; i < array_size; i++) {
    input_array[i] =
        rand() % 2001 - 1000; /* -1000 to 1000, so duplicates and negatives */
  }
  my_mergesort_test(test_case_name, input_array, array_size);
  free(input_array);
}

int main(void) {
  srand(12345);

  int t1[] = {42};
  my_mergesort_test("one element", t1, 1);

  int t2[] = {1, 2};
  my_mergesort_test("two elements, in order", t2, 2);

  int t3[] = {2, 1};
  my_mergesort_test("two elements, reversed", t3, 2);

  int t4[] = {5, 2, 9, 1, 7, 3};
  my_mergesort_test("six elements (even length)", t4, 6);

  int t5[] = {5, 2, 9, 1, 7, 3, 8};
  my_mergesort_test("seven elements (odd length)", t5, 7);

  int t6[] = {1, 2, 3, 4, 5, 6, 7, 8};
  my_mergesort_test("already sorted", t6, 8);

  int t7[] = {8, 7, 6, 5, 4, 3, 2, 1};
  my_mergesort_test("reverse sorted", t7, 8);

  int t8[] = {4, 4, 4, 4, 4};
  my_mergesort_test("all the same", t8, 5);

  int t9[] = {-5, 3, -1, 0, -8, 7, 3, -5};
  my_mergesort_test("negatives and duplicates", t9, 8);

  run_random_test("random, 100 elements", 100);
  run_random_test("random, 1001 elements", 1001);
  run_random_test("random, 100000 elements", 100000);

  return 0;
}