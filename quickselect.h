#ifndef QUICKSELECT_H
#define QUICKSELECT_H

void swap(double *a, double *b);

int partition(double *array, int left_pointer, int right_pointer);

double quickselect(double *array, int left_index, int right_index, int kth_lowest_value);

#endif