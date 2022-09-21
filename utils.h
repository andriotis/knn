#ifndef UTILS_H
#define UTILS_H

double **create_dataset();

void print_dataset(double **X);

double **get_random_sample(double **Set, int size, int sample_size, int num_shuffles);

double euclidean_dist(double *point1, double *point2);

double get_median(double *data, int size);

#endif