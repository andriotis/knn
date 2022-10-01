#ifndef QUICKSELECT_H
#define QUICKSELECT_H

void point_swap(double **a, double **b);
void dist_swap(double *a, double *b);
int partition(double *distances, int l, int r);
double quickselect(double *distances, int l, int r, int k);
#endif