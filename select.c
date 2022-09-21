#include "select.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern DIM;

double *select_random_vp(double **Set, int size)
{
    int rand_idx = ((double)rand() / RAND_MAX) * size;
    return Set[rand_idx];
}

double *select_last_vp(double **Set, int size)
{
    return Set[size - 1];
}

double *select_best_vp(double **Set, int size)
{
    int SAMPLE_SIZE = size / 10;
    int NUM_SHUFFLES = size / 2;

    // P is a random subset of Set
    double **P = get_random_sample(Set, size, SAMPLE_SIZE, NUM_SHUFFLES);
    double best_spread = 0;
    double *best_p = (double *)malloc(DIM * sizeof(double));

    for (int i = 0; i < SAMPLE_SIZE; i++)
    {
        double *current_p = P[i];
        // D is a random subset of Set
        double **D = get_random_sample(Set, size, SAMPLE_SIZE, NUM_SHUFFLES);
        // Calculate distance of current_p fromevery point of D
        double *dists = (double *)malloc(SAMPLE_SIZE * sizeof(double));
        for (int j = 0; j < SAMPLE_SIZE; j++)
            dists[j] = euclidean_dist(D[j], current_p);

        // Calculate median of dists
        double median = get_median(dists, SAMPLE_SIZE);

        // Compute 2nd moment
        double spread = 0;
        for (int j = 0; j < SAMPLE_SIZE; j++)
            spread += pow(dists[j] - median, 2.0);
        spread /= SAMPLE_SIZE;

        if (spread > best_spread)
        {
            best_spread = spread;
            best_p = current_p;
        }
    }

    return best_p;
}