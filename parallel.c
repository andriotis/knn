#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"
#include "structures.h"

int n = 8;
int d = 2;
int t = 4;

double *S;

pthread_mutex_t mutex;

typedef struct
{
    int start;
    int end;
} foo;

void *add_value(void *params)
{
    foo *args = (foo *)params;
    for (int i = args->start; i < args->end; i++)
        S[i] = (double)i;
}

int main()
{
    int n = 16;
    int t = 4;
    S = (double *)calloc(n, sizeof(double));
    for (int i = 0; i < n; i++)
        printf("%f ", S[i]);
    printf("\n");

    pthread_t th[t];
    foo f[t];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < t; i++)
    {
        f[i].start = i * t;
        f[i].end = (i + 1) * t;
        pthread_create(&th[i], NULL, &add_value, (void *)&f[i]);
    }

    for (int i = 0; i < t; i++)
        pthread_join(th[i], NULL);

    pthread_mutex_destroy(&mutex);

    for (int i = 0; i < n; i++)
        printf("%f ", S[i]);
    printf("\n");

    return EXIT_SUCCESS;
}