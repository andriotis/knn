#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"
#include "structures.h"

int n = 21;
int d = 2;
int t = 4;

int *S;

pthread_mutex_t mutex;

typedef struct
{
    int start;
    int end;
} foo;
// Read below to understand
// https://stackoverflow.com/questions/36688900/divide-an-uneven-number-between-threads
void bar(foo *f)
{
    int *a = (int *)calloc(t, sizeof(int));
    for (int i = 0; i < t; i++)
    {
        a[i] = n / t;
        if (i < n % t)
            a[i] += 1;

        f[i].start = 0;

        for (int j = 0; j < i; j++)
            f[i].start += a[j];
        f[i].end = f[i].start + a[i];
    }
}

void *put_index_as_value(void *params)
{
    foo *args = (foo *)params;
    for (int i = args->start; i < args->end; i++)
        S[i] = (int)i;
}

int main()
{
    S = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);
    printf("\n");

    pthread_t *th = (pthread_t *)malloc(t * sizeof(pthread_t));
    foo *f = (foo *)malloc(t * sizeof(foo));
    bar(f);

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < t; i++)
        pthread_create(&th[i], NULL, &put_index_as_value, (void *)&f[i]);

    for (int i = 0; i < t; i++)
        pthread_join(th[i], NULL);

    pthread_mutex_destroy(&mutex);

    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);
    printf("\n");

    return EXIT_SUCCESS;
}