#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "quickselect.h"
#include "structures.h"

extern int d;

/* Given 2 points, it returns the euclidean distance between them */
double euclidean_dist(double *point1, double *point2)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    dist += pow(point2[i] - point1[i], 2.0);
  return sqrt(dist);
}

// TODO: Check if else statement can be avoided. See process_distribution repo on github
/* Given an array, it returns the median of the values in it */
double get_median(double *array, int size)
{
  if (size % 2 == 0)
    return (quickselect(array, 0, size - 1, size / 2) +
            quickselect(array, 0, size - 1, (size - 1) / 2)) /
           2;
  else
    return quickselect(array, 0, size - 1, (size - 1) / 2);
}