#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "quickselect.h"
#include "structures.h"

extern int d;
extern double **points;
extern double *distances;

double euclidean_dist(double *a, double *b)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    dist += pow(b[i] - a[i], 2.0);
  return sqrt(dist);
}

double get_median(Set X)
{
  return (quickselect(X.start, X.end - 1, (X.end - X.start - 1) / 2 + 1) +
          quickselect(X.start, X.end - 1, (X.end - X.start) / 2 + 1)) /
         2;
}

void calc_dist_seq(Set X)
{
  for (int i = X.start; i < X.end; i++)
    distances[i] = euclidean_dist(points[i], points[X.end]);
}