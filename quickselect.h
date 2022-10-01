#ifndef QUICKSELECT_H
#define QUICKSELECT_H

void point_swap(double **a, double **b);
void dist_swap(double *a, double *b);
int partition(int l, int r);
double quickselect(int l, int r, int k);
#endif