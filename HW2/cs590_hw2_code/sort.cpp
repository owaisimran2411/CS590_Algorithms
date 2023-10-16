#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <iostream>

/*
  * Student Name: Muhammad Owais Imran
  * CWID: 20025554
  * Course: CS590-B
  * HW # 02
*/

#include "sort.h"
using namespace std;

/*
 * HW 2 part
 */
int string_compare(char *s1, char *s2)
{
  /*
   * We assume that s1 and s2 are non-null pointers
   */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
  {
    if (s1[i] < s2[i])
      return -1;
    else
      return 1;
  }
} /*>>>*/

void insertion_sort(char **A, int l, int r)
{
  int i;
  char *key;

  for (int j = l + 1; j <= r; j++) {
    key = A[j];
    i = j - 1;

    while ((i >= l) && (string_compare(A[i], key) > 0)) {
      A[i + 1] = A[i];
      i = i - 1;
    }

    A[i + 1] = key;
  }
}


/*
  * Helper Function to calculate maxLengthString
*/ 
int getMaxLengthString(int *A_len, int numberOfStrings) {
  int max = INT_MIN;
  for(int i=0; i<numberOfStrings; i++) {
    if (A_len[i]>max) {
      max = A_len[i];
    }
  }
  return max;
}

void insertion_sort_digit(char **A, int *A_len, int l, int r, int d)
{
  int i;
  char *key;
  int key_len;

  for (int j = l + 1; j <= r; j++) {
    key = A[j];
    key_len = A_len[j];
    i = j - 1;

    while (i >= l && (d >= 0) && (string_compare(A[i], key) > 0)) {
      A[i + 1] = A[i];
      A_len[i + 1] = A_len[i];
      i = i - 1;
    }

    A[i + 1] = key;
    A_len[i + 1] = key_len;
  }
}

void counting_sort_digit(char **A, int *A_len, char **B, int *B_len, int n, int d)
{
  int counter[256] = {0};

  // counting occurence
  for(int i=0; i<n; i++) {
    if (A_len[i] > d) {
      counter[A[i][d]]++;
    }
    else {
      counter[0]++;
    }
  }

  // Calculate CF for counter
  for(int i=1; i<256; i++) {
    counter[i] += counter[i-1];
  }

  // creating B using counters
  for(int i=n-1; i>=0; i--) {
    if(A_len[i]>d) {
      char atD = A[i][d];
      int position = counter[atD]--;
      B[position-1]=A[i];
      B_len[position-1]=A_len[i];
    }
    else {
      int position = counter[0]--;
      B[position-1] = A[i];
      B_len[position-1] = A_len[i];
    }
  }

  // updating A with values in B
  for(int i=0; i<n; i++) {
    A[i] = B[i];
    A_len[i] = B_len[i];
  }
}

void radix_sort_is(char** A, int* A_len, int n, int m)
{
  int maximumLength = getMaxLengthString(A_len, n);

  // Radix sort from the least significant character to the most significant character
  for(int pos=maximumLength-1; pos>=0; pos--) {
    insertion_sort_digit(A, A_len, 0, n-1, pos);
  }
}


void radix_sort_cs(char **A, int *A_len, int n, int m)
{
  int maximumLength = getMaxLengthString(A_len, n);

  // Radix sort from the least significant character to the most significant character
  for(int pos=maximumLength-1; pos>=0; pos--) {
    char *B[n];
    int B_len[n];
    counting_sort_digit(A, A_len, B, B_len, n, pos);
  }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(char **A, int l, int r)
{
  for (int i = l + 1; i < r; i++)
    if (string_compare(A[i - 1], A[i]) > 0)
      return false;
  return true;
}
