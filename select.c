#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "select.h"
#include "structures.h"

extern DIM;

Point select_random_vp(Set Set)
{
    Point p;
    p.idx = ((double)rand() / RAND_MAX) * Set.size;
    p.value = Set.points[p.idx];
    return p;
}

Point select_last_vp(Set S)
{
    Point p;
    p.idx = S.size - 1;
    p.value = S.points[p.idx];
    return p;
}

Point select_best_vp(Set S)
{
    int SAMPLE_SIZE = S.size / 10;
    int NUM_SHUFFLES = S.size / 2;

    // P is a random subset of Set
    Set P = get_random_sample(S, SAMPLE_SIZE, NUM_SHUFFLES);
    double best_spread = 0;

    Point best_p;
    best_p.value = (double *)malloc(DIM * sizeof(double));

    for (int i = 0; i < SAMPLE_SIZE; i++)
    {
        Point current_p;
        current_p.idx = i;
        current_p.value = P.points[current_p.idx];

        // D is a random subset of Set
        Set D = get_random_sample(S, SAMPLE_SIZE, NUM_SHUFFLES);

        // Calculate distance of current_p fromevery point of D
        double *dists = (double *)malloc(SAMPLE_SIZE * sizeof(double));
        for (int j = 0; j < SAMPLE_SIZE; j++)
            dists[j] = euclidean_dist(D.points[j], current_p.value);

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

// // Set to split in L and R
// Set S = {X.start, X.end - 1};
// int set_size = S.end - S.start + 1;

// // Find inner set's bounds
// Set L = {S.start, S.start + (set_size / 2) - 1};

// // Find outer set's bounds
// Set R = {L.end + 1, S.end};