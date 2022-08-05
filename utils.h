#ifndef UTILS_H
#define UTILS_H

double **create_dataset();

void print_dataset(double **X);

double euclidean_dist(double *point1, double *point2, int dim);

double get_median(double *data, int size);

#endif