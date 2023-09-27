#include <cstdio>
#include <cstdlib>
#include<iostream>
#include<limits.h>

#include "sort.h"
using namespace std;

/*
  * Student Name: Muhammad Owais Imran
  * CWID: 20025554
  * Course: CS590-B
  * HW # 01
*/

int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int** A, int n, int l, int r)
{

  // Calculating the length of each sub array in A
  int *preComputedLengths = new int[r+1];
  for (int count=0; count<r+1; count++) {
    preComputedLengths[count] = ivector_length(A[count], n);
  }

  // running the insertion sort algorithm
  int i;
  int *keyArray=new int[r+1];
  int keyPreComputedLength;

  for(int j=l+1; j<=r; j++) {
    keyArray=A[j];
    keyPreComputedLength=preComputedLengths[j];
    i=j-1;
    while((i>=0) && keyPreComputedLength<preComputedLengths[i]) {
      preComputedLengths[i+1]=preComputedLengths[i];
      A[i+1]=A[i];
      i--;
    }
    A[i+1]=keyArray;
    preComputedLengths[i+1]=keyPreComputedLength;
  }
}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/
void merge_sort(int** A, int n, int p, int r)
{
  // Calculating the length of each sub array in A
  int *preComputedLengths = new int[r+1];
  for (int count=0; count<r+1; count++) {
    preComputedLengths[count] = ivector_length(A[count], n);
  }

  mergeSort(A, p, r, preComputedLengths, n);
}

/*
* FUNCTION TO START MERGE SORT EXECUTION
*/
void mergeSort(int **A, int left, int right, int *preComputerLength, int dimension) {
  if (left<right) {
    int mid = left + (right-left) / 2;
    mergeSort(A,left,mid,preComputerLength,dimension);
    mergeSort(A,mid+1,right,preComputerLength,dimension);

    mergeArrays(A,left,mid,right,preComputerLength,dimension);
  }
}


/*
* FUNCTION TO MERGE TWO ARRAYS
*/
void mergeArrays(int **A, int p, int q, int r, int *preComputedLengths, int dimension) {

  int leftLength = q-p+1;
  int rightLength = r-q;

  // creating two subarray to merge the preComputerLengths array
  int *leftLengthArray = new int[leftLength+1];
  int *rightLengthArray = new int[rightLength+1];

  // creating two subarrays to merge the main 2d array
  int **leftMainArray = new int*[leftLength];
  int **rightMainArray = new int*[rightLength];
  
  for(int count=0; count<leftLength; count++) {
    leftMainArray[count] = new int[dimension];
    leftMainArray[count] =  A[p+count];
    leftLengthArray[count] = preComputedLengths[count+p];
  }
  for(int count=0; count<rightLength; count++) {
    rightMainArray[count] = new int[dimension];
    rightMainArray[count] = A[q+count+1];
    rightLengthArray[count] = preComputedLengths[q+count+1];
  }

  // placing sentinels on the ending index of leftLength and rightLength
  leftLengthArray[leftLength]=INT_MAX;
  rightLengthArray[rightLength]=INT_MAX;

  int i,j,k;
  i=0;
  j=0;
  k=p;

  while(i<leftLength && j<rightLength) {
    if (leftLengthArray[i] <= rightLengthArray[j]) {
      preComputedLengths[k] = leftLengthArray[i];
      A[k] = leftMainArray[i];
      i++;
    }
    else {
      preComputedLengths[k] = rightLengthArray[j];
      A[k] = rightMainArray[j];
      j++;
    }
    k++;
  }

  while(i<leftLength) {
    preComputedLengths[k] = leftLengthArray[i];
    A[k] = leftMainArray[i];
    i++;
    k++;
  }

  while(j<rightLength) {
    preComputedLengths[k] = rightLengthArray[j];
    A[k] = rightMainArray[j];
    j++;
    k++;
  }

}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

