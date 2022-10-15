#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "main.h"

#include "brute.h"
#include "sequential.h"
#include "parallel.h"

int n, d, k;
double tau;
double **points;
double *query;
double *distances;

void print_usage()
{
    printf("\nUSAGE\n");
    printf("\t--n : number of points\n");
    printf("\t--d : number of dimensions\n");
    printf("\t--k : number of neighbors\n");
    printf("\t--brute : bruteforce search\n");
    printf("\t--sequential : sequential search\n");
    printf("\t--parallel : parallel search\n");
    printf("\t--all : all the three together search\n");
    printf("\nEXAMPLE\n");
    printf("\nTo search the 4 nearest neighbors of a query amongst 1000 points of dimension 5 sequentially, type the following command:\n");
    printf("\n\t./main --n=1000 --d=5 --k=4 --sequential\n\n");
}

void initialize_knn()
{
    // initialize points
    points = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        points[i] = malloc(d * sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            points[i][j] = (double)rand() / RAND_MAX;

    // initialize query
    query = malloc(d * sizeof(double));
    for (int i = 0; i < d; i++)
        query[i] = (double)rand() / RAND_MAX;

    // initialize distances
    distances = malloc(n * sizeof(double));
}

void free_knn()
{
    free(points);
    free(distances);
    free(query);
}

int main(int argc, char *argv[])
{
    int opt = 0;
    int s = 0, p = 0, b = 0;
    static struct option long_options[] = {
        {"n", required_argument, 0, 'n'},
        {"d", required_argument, 0, 'd'},
        {"k", required_argument, 0, 'k'},
        {"sequential", no_argument, 0, 's'},
        {"parallel", no_argument, 0, 'p'},
        {"brute", no_argument, 0, 'b'},
        {"all", no_argument, 0, 'a'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    int long_index = 0;
    while ((opt = getopt_long(argc, argv, "",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'n':
            n = atoi(optarg);
            break;
        case 'd':
            d = atoi(optarg);
            break;
        case 'k':
            k = atoi(optarg);
            break;
        case 's':
            s = 1;
            break;
        case 'p':
            p = 1;
            break;
        case 'b':
            b = 1;
            break;
        case 'a':
            s = 1;
            p = 1;
            b = 1;
            break;
        case 'h':
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    // if the right amount of args are not given
    if (long_index < 2)
    {
        print_usage();
        return EXIT_FAILURE;
    }
    // if only sequential
    if (s == 1 && p == 0 && b == 0)
    {
        srand(42);
        initialize_knn();
        run_sequential();
        free_knn();
    }
    // if only parallel
    else if (s == 0 && p == 1 && b == 0)
    {
        srand(42);
        initialize_knn();
        run_parallel();
        free_knn();
    }
    // if only brute
    else if (s == 0 && p == 0 && b == 1)
    {
        srand(42);
        initialize_knn();
        run_brute();
        free_knn();
    }
    // everything
    else
    {
        srand(42);
        initialize_knn();
        run_sequential();
        free_knn();

        srand(42);
        initialize_knn();
        run_parallel();
        free_knn();

        srand(42);
        initialize_knn();
        run_brute();
        free_knn();
    }

    return EXIT_SUCCESS;
}