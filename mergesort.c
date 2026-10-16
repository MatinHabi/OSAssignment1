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
/* sorts A[left..right]. splits into two halves until cutoff level and then merges.*/
/* doesn't free its own arg but the caller does. */
void* parallel_mergesort(void* arg) {
  struct argument *my_arg = (struct argument *)arg;
  struct argument *left_arg;
  struct argument *right_arg;

  pthread_t left_thread;
  pthread_t right_thread;

  int left_started = FALSE;
  int right_started = FALSE ;
  int left, right, level, mid, rc;

  if (my_arg == NULL){
    return NULL;
  }
  left = my_arg->left;
  right = my_arg->right;
  level = my_arg->level;

  /*base case: either deep enough in the thread tree or nothing left to split*/
  if (level >= cutoff || right - left < 1){
    my_mergesort(left, right);
    return NULL;
  }


mid = left + (right-left)/2;

/* separate args so the halves never have to share one */
left_arg = buildArgs(left, mid, level+1);
right_arg = buildArgs(mid+1, right, level+1);

 if (left_arg != NULL &&
      pthread_create(&left_thread, NULL, parallel_mergesort, left_arg) == 0) {
    left_started = TRUE;
  }
  if (right_arg != NULL &&
      pthread_create(&right_thread, NULL, parallel_mergesort, right_arg) == 0) {
    right_started = TRUE;
  }

  /* if no thread for a half, sort it ourselves */
  if (!left_started) {
    my_mergesort(left, mid);
  }
  if (!right_started) {
    my_mergesort(mid + 1, right);
  }

  /* both halves must finish before merge */
  if (left_started) {
    rc = pthread_join(left_thread, NULL);
    if (rc != 0) {
      fprintf(stderr, "pthread_join failed: %s\n", strerror(rc));
      exit(EXIT_FAILURE);
    }
  }
  if (right_started) {
    rc = pthread_join(right_thread, NULL);
    if (rc != 0) {
      fprintf(stderr, "pthread_join failed: %s\n", strerror(rc));
      exit(EXIT_FAILURE);
    }
  }

free(left_arg);
free(right_arg);

merge(left, mid, mid+1, right);
return NULL;
}

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
