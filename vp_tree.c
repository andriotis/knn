#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int N, D;

typedef struct VPTree {
  double *vp;
  double md;
  int idx;
  struct VPTree *inner;
  struct VPTree *outer;
} VPTree;


int main(int argc, char **argv) {

  N = atoi(argv[1]);
  D = atoi(argv[2]);

  double **X = create_dataset();
  print_dataset(X);

  return EXIT_SUCCESS;
}