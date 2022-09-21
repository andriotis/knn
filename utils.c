#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "quickselect.h"

extern int NUM_POINTS, DIM;

double **create_dataset()
{

  double **X;

  X = (double **)malloc(NUM_POINTS * sizeof(double *));
  for (int i = 0; i < NUM_POINTS; i++)
  {
    X[i] = (double *)malloc(DIM * sizeof(double));
  }

  for (int i = 0; i < NUM_POINTS; i++)
  {
    for (int j = 0; j < DIM; j++)
    {
      X[i][j] = (double)rand() / (double)RAND_MAX;
    }
  }

  return X;
}

void print_dataset(double **X)
{
  for (int i = 0; i < NUM_POINTS; i++)
  {
    for (int j = 0; j < DIM; j++)
      printf("%lf ", X[i][j]);
    printf("\n");
  }
}

// Given a set of point returns a random sample of a certain size
double **get_random_sample(double **Set, int size, int sample_size, int num_shuffles)
{
  // Create empty matrix to store smamples (subset of Set)
  double **sample = (double **)malloc(sample_size * sizeof(double *));
  for (int i = 0; i < sample_size; i++)
  {
    sample[i] = (double *)malloc(DIM * sizeof(double));
  }

  // Create array that contains the Set's indexes
  int *setIndexes = (int *)malloc(size * sizeof(int));
  for (int i = 0; i < size; i++)
    setIndexes[i] = i;

  // Shuffle set indexs array
  srand(3); // constant seed for testing
  for (int j = 0; j < num_shuffles; j++)
  {
    for (int i = 0; i < size; i++)
    {
      size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
      int tmp = setIndexes[j];
      setIndexes[j] = setIndexes[i];
      setIndexes[i] = tmp;
    }
  }

  // Select the first 'sample_size' indexes to construct the sample
  for (int i = 0; i < sample_size; i++)
  {
    sample[i] = Set[setIndexes[i]];
  }

  return sample;
}

/* Given 2 points, it returns the euclidean distance between them */
double euclidean_dist(double *point1, double *point2)
{
  double dist = 0.0;
  for (int i = 0; i < DIM; i++)
    dist += pow(point2[i] - point1[i], 2.0);
  return sqrt(dist);
}

/* Given an array, it returns the median of the values in it */
double get_median(double *arr, int size)
{
  return (quickselect(arr, 0, size - 1, size / 2) +
          quickselect(arr, 0, size - 1, size / 2 + 1)) /
         2;
}
