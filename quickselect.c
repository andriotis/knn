#include "quickselect.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(double *a, double *b)
{
  double temp = *a;
  *a = *b;
  *b = temp;
}

int partition(double *arr, int l, int r)
{
  double x = arr[r];
  int i = l;
  for (int j = l; j <= r - 1; j++)
  {
    if (arr[j] <= x)
    {
      swap(&arr[i], &arr[j]);
      i++;
    }
  }
  swap(&arr[i], &arr[r]);
  return i;
}

double quickselect(double *arr, int l, int r, int k)
{
  if (k > 0 && k <= r - l + 1)
  {

    int index = partition(arr, l, r);

    if (index - l == k - 1)
      return arr[index];

    if (index - l > k - 1)
      return quickselect(arr, l, index - 1, k);

    return quickselect(arr, index + 1, r,
                       k - index + l - 1);
  }
  return 0;
}