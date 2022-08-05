#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "quickselect.h"

extern int N, D;

double **create_dataset() {

  double **X;

  X = (double **) malloc(N * sizeof(double *));
  for (int i = 0; i < N; i++) {
    X[i] = (double *) malloc(D * sizeof(double));
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) {
      X[i][j] = (double)rand() / (double)RAND_MAX;
    }
  }

  return X;

}

void print_dataset(double **X) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++)
      printf("%lf ", X[i][j]);
    printf("\n");
  }
}

/* Given 2 points, it returns the euclidean distance between them */  
double euclidean_dist(double *point1, double *point2, int dim) {
  double dist = 0.0;
  for (int i = 0; i < dim; i++) dist += pow(point2[i] - point1[i], 2.0);
  return sqrt(dist);
}

/* Given an array, it returns the median of the values in it */
double get_median(double *arr, int size) {
  return (quickselect(arr, 0, size - 1, size / 2) +
          quickselect(arr, 0, size - 1, size / 2 + 1)) /
         2;
}
