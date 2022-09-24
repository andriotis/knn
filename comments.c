typedef struct point
{
    double *values;
    int size;
} Point;

typedef struct Set
{
    double **points;
    int size;
} Set;

double *select_random_vp(Set S);
double *euclidean(Point a, Point b);