#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "quickselect.h"
#include "structures.h"

extern int d;

/* Given 2 points, it returns the euclidean distance between them */
double euclidean_dist(double *a, double *b)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    dist += pow(b[i] - a[i], 2.0);
  return sqrt(dist);
}

// TODO: Check if else statement can be avoided. See process_distribution repo on github
/* Given an array, it returns the median of the values in it */
double get_median(Set X)
{
  int size = X.end - X.start + 1;

  return (quickselect(X.start, size - 1, size / 2 + 1) +
          quickselect(X.start, size - 1, (size - 1) / 2 + 1)) /
         2;
}