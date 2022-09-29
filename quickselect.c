#include "quickselect.h"
#include <stdio.h>

void swap(double *a, double *b)
{
  double temp = *a;
  *a = *b;
  *b = temp;
}

int partition(double *array, int left_pointer, int right_pointer)
{
  int pivot_position = right_pointer;
  double pivot = array[pivot_position];

  right_pointer -= 1;

  while (1)
  {
    while (array[left_pointer] < pivot)
      left_pointer += 1;

    while (array[right_pointer] > pivot)
      right_pointer -= 1;

    if (left_pointer >= right_pointer)
      break;
    else
      swap(&array[left_pointer], &array[right_pointer]);
  }

  swap(&array[left_pointer], &array[pivot_position]);

  return left_pointer;
}

double quickselect(double *array, int left_index, int right_index, int kth_lowest_value)
{
  if (right_index <= left_index)
    return array[left_index];

  int pivot_position = partition(array, left_index, right_index);

  if (kth_lowest_value < pivot_position)
    quickselect(array, kth_lowest_value, left_index, pivot_position - 1);

  else if (kth_lowest_value > pivot_position)
    quickselect(array, kth_lowest_value, pivot_position + 1, right_index);

  else
    return array[pivot_position];
}