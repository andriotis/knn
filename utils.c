#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "quickselect.h"
#include "structures.h"

extern int d;

// Set create_dataset(int size)
// {

//   Set Set;
//   Set.size = size;

//   Set.points = (double **)malloc(Set.size * sizeof(double *));
//   for (int i = 0; i < Set.size; i++)
//   {
//     Set.points[i] = (double *)malloc(DIM * sizeof(double));
//   }

//   for (int i = 0; i < Set.size; i++)
//   {
//     for (int j = 0; j < DIM; j++)
//     {
//       Set.points[i][j] = (double)rand() / (double)RAND_MAX;
//     }
//   }

//   return Set;
// }

// void print_dataset(Set Set)
// {
//   for (int i = 0; i < Set.size; i++)
//   {
//     for (int j = 0; j < DIM; j++)
//       printf("%lf ", Set.points[i][j]);
//     printf("\n");
//   }
// }

// // Given a set of point returns a random sample of a certain size
// Set get_random_sample(Set S, int sample_size, int num_shuffles)
// {
//   // Create empty matrix to store smamples (subset of Set)
//   Set sample;
//   sample.size = sample_size;

//   sample.points = (double **)malloc(sample_size * sizeof(double *));
//   for (int i = 0; i < sample_size; i++)
//   {
//     sample.points[i] = (double *)malloc(DIM * sizeof(double));
//   }

//   // Create array that contains the Set's indexes
//   int *setIndexes = (int *)malloc(S.size * sizeof(int));
//   for (int i = 0; i < S.size; i++)
//     setIndexes[i] = i;

//   // Shuffle set indexs array
//   srand(3); // constant seed for testing
//   for (int j = 0; j < num_shuffles; j++)
//   {
//     for (int i = 0; i < S.size; i++)
//     {
//       size_t j = i + rand() / (RAND_MAX / (S.size - i) + 1);
//       int tmp = setIndexes[j];
//       setIndexes[j] = setIndexes[i];
//       setIndexes[i] = tmp;
//     }
//   }

//   // Select the first 'sample_size' indexes to construct the sample
//   for (int i = 0; i < sample_size; i++)
//   {
//     sample.points[i] = S.points[setIndexes[i]];
//   }
//   return sample;
// }

/* Given 2 points, it returns the euclidean distance between them */
double euclidean_dist(double *point1, double *point2)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    printf("%f ", point1[i]);
  printf("\n");
  for (int i = 0; i < d; i++)
    printf("%f ", point2[i]);
  printf("\n");
  for (int i = 0; i < d; i++)
    dist += pow(point2[i] - point1[i], 2.0);
  return sqrt(dist);
}

// TODO: Check if else statement can be avoided. See process_distribution repo on github
/* Given an array, it returns the median of the values in it */
double get_median(double *arr, int size)
{
  if (size % 2 == 0)
  {
    if (size > 2)
    {
      return (quickselect(arr, 0, size - 1, (size - 1) / 2) +
              quickselect(arr, 0, size - 1, (size - 1) / 2 + 1)) /
             2;
    }
    else
    {
      return (arr[0] + arr[1]) / 2;
    }
  }
  else
  {
    return quickselect(arr, 0, size - 1, size / 2);
  }
}
