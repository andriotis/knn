#include "quickselect.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

extern double **points;
extern double *distances;

void point_swap(double **a, double **b)
{
  double *temp = *a;
  *a = *b;
  *b = temp;
}

void dist_swap(double *a, double *b)
{
  double temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int l, int r)
{
  double x = distances[r];
  int i = l;
  for (int j = l; j <= r - 1; j++)
  {
    if (distances[j] <= x)
    {
      dist_swap(&distances[i], &distances[j]);
      point_swap(&points[i], &points[j]);
      i++;
    }
  }
  dist_swap(&distances[i], &distances[r]);
  point_swap(&points[i], &points[r]);
  return i;
}

double quickselect(int l, int r, int k)
{
  if (k > 0 && k <= r - l + 1)
  {
    int index = partition(l, r);

    if (index - l == k - 1)
      return distances[index];

    if (index - l > k - 1)
      return quickselect(l, index - 1, k);

    return quickselect(index + 1, r, k - index + l - 1);
  }
  return 0;
}