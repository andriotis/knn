#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "queue.h"

// EXPERIMENT VARIABLES SHOULD BE GLOBAL
extern int n, d, k;
extern double **points;
extern double *query;
extern double *distances;

// RUNTIME VARIABLES SHOULD BE LOCAL
extern double tau;
struct LinkedList *nearest;

// RUN BRUTEFORCE AND DISPLAY DISTANCES
void run_brute()
{
    tau = RAND_MAX;
    nearest = newNode(-1, RAND_MAX);

    double distance;

    clock_t start = clock();
    for (int i = 0; i < n; i++)
    {
        distance = euclidean_dist(query, points[i]);
        if (distance < tau)
        {
            push(&nearest, i, distance);
            if (size(&nearest) > k)
                pop(&nearest);
            if (size(&nearest) == k)
                tau = peek(&nearest)->distance;
        }
    }
    clock_t end = clock();
    printf("Brute took : %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}