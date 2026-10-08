/**
 * This file implements parallel mergesort.
 */

#include "mergesort.h"

#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memcpy */

/* this function will be called by mergesort() and also by parallel_mergesort().
 */
void merge(int leftstart, int leftend, int rightstart, int rightend) {
  /*Create pointers for the arrays*/
  int i = leftstart;   // Left Array
  int j = rightstart;  // Right Array
  int k = leftstart;   // B

  /*Main loop for comparing elements of left and right array to populate final
   * array*/
  while (i <= leftend && j <= rightend) {
    if (A[i] <= A[j]) {
      B[k] = A[i];
      i++;
    } else {
      B[k] = A[j];
      j++;
    }
    k++;
  }

  /*Copy the remaining elements of left side of A*/
  while (i <= leftend) {
    B[k] = A[i];
    i++;
    k++;
  }

  /*Copy the remaining elements of right side of A*/
  while (j <= rightend) {
    B[k] = A[j];
    j++;
    k++;
  }

  /*Copy values of B into A */
  memcpy(A + leftstart, B + leftstart,
         (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parllel_mergesort() as its base case. */
void my_mergesort(int left, int right) {
  if (left < right) {
    /*Declare merge variables*/
    int leftstart = left;
    int leftend = left + (right - left) / 2;
    int rightstart = leftend + 1;
    int rightend = right;

    my_mergesort(leftstart, leftend);    // merge sort on left side
    my_mergesort(rightstart, rightend);  // merge sort of right

    merge(leftstart, leftend, rightstart, rightend);
  }
}

/* this function will be called by the testing program. */
void* parallel_mergesort(void* arg) { return NULL; }

/* we build the argument for the parallel_mergesort function. */
struct argument *buildArgs(int left, int right, int level)
{
    struct argument *arg = malloc(sizeof(*arg));
    if (arg == NULL) {
        return NULL;
    }

    arg->left = left;
    arg->right = right;
    arg->level = level;

    return arg;
}
