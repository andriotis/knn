#include "vp_tree.h"
#include "structures.h"
#include "select.h"
#include "utils.h"

extern int DIM;

VPTree *get_vp_tree(Set S)
{
  VPTree *node;
  // Select a vantage point
  Point vp = select_last_vp(S);
  node->vp = vp.value;

  // Save vantage point's index in the original set
  node->idx = vp.value;

  // Calculate the distance of the pv from every point in the set
  double *distances = (double *)malloc(S.size * sizeof(double));
  for (int i = 0; i < S.size; i++)
    distances[i] = euclidean_dist(S.points[i], node->vp);
  // Find median distance
  node->md = get_median(distances, S.size);

  // Split set in outer and inner
  Set Inner, Outer;
  /*
    Allocate space to hold points for each set.
    The maximum required size for each set equals the size of Set
  */
  Inner.points = (double **)malloc(S.size * sizeof(double *));
  Outer.points = (double **)malloc(S.size * sizeof(double *));
  for (int i = 0; i < S.size; i++)
  {
    Inner.points[i] = (double *)malloc(DIM * sizeof(double));
    Outer.points[i] = (double *)malloc(DIM * sizeof(double));
  }

  // Current size of each set (denotes the index where the next element should be placed)
  int inner_size = 0, outer_size = 0;
  // Split Set points two Inner and Outer sets
  for (int i = 0; i < S.size; i++)
  {
    if (distances[i] < node->md)
    {
      // Add point in inner set
      Inner.points[inner_size] = S.points[i];
      inner_size++;
    }
    else
    {
      // Add point in outer set
      Outer.points[outer_size] = S.points[i];
      outer_size++;
    }
  }

  // Reallocate memory so every set has the minimum required size
  Inner.points = (double **)realloc(Inner.points, inner_size * sizeof(double *));
  Outer.points = (double **)realloc(Outer.points, outer_size * sizeof(double *));

  // Create inner and outer subtrees recursively
  node->inner = get_vp_tree(Inner);
  node->outer = get_vp_tree(Outer);

  return node;
}