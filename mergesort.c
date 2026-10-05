/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){	
	/*Create pointers for the arrays*/
	int i = leftstart; // Left Array 
	int j = rightstart; // Right Array 
	int k = leftstart; // B 

	/*Main loop for comparing elements of left and right array to populate final array*/
    while (i <= leftend && j <= rightend) {
        if (A[i] <= A[j]) {
        	B[k] = A[i];
            i++;
        }
        else {
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
   memcpy(A + leftstart, B + leftstart, (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parllel_mergesort() as its base case. */
void my_mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

