/*
  Pirvulescu Andreea Monica

  Not optimized version
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/* compute dsymv */
int simple_dsymv(int n, double alpha, double **a, double *x, double beta, double *y, double *res)
{

    int i, j;
    double *z;

    z = (double *)calloc(n, sizeof(double));

    for (i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            z[i] += a[i][j] * x[j];

    for (i = 0; i < n; i++)
        res[i] = alpha * z[i] + beta * y[i];

    free(z);

    return 0;

}

void test(int n, double *a, double *b)
{

    int ok = 0, i;

    for (i = 0; i < n; i++)
        if (a[i] != b[i])
        {
            printf("The result is not correct!\n");
            ok = 1;
        }

    if (ok == 0)
        printf("The result is correct!\n");

}

int main(int argc, char * argv[])
{

    int n, i, j, it = 0;
    double time_spent_simple, time_spent_atlas;

    if (argc != 2)
    {
        printf("Erorr! Usage: ./simple_dsymv dimension\n");
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);

    double **a, *x, *y, *res, *vect_a;
    double alpha, beta;

    a = (double **)calloc(n,sizeof(double *));
    for (i = 0; i < n; i++)
        a[i] = (double *)calloc(n, sizeof(double));

    x = (double *)calloc(n, sizeof(double));
    y = (double *)calloc(n, sizeof(double));
    res = (double *)calloc(n, sizeof(double));
    vect_a = (double *)calloc(n*n, sizeof(double));

    /* generate values */
    srand(time(NULL));
    alpha = rand() % n;
    beta = rand() % n;

    for (i = 0; i < n; i++)
    {

        x[i] = rand() % n;
        y[i] = rand() % n;

        for (j = 0; j <= i; j++)
            a[i][j] = a[j][i] = rand() % n;
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            vect_a[it] = a[i][j];
            it++;
        }

    /* Multiplication */

    /* not optimized version */
    struct timeval start1, stop1;
    gettimeofday(&start1, NULL);
    simple_dsymv(n, alpha, a, x, beta, y, res);
    gettimeofday(&stop1, NULL);
    time_spent_simple = ((stop1.tv_sec * 1000 + stop1.tv_usec / 1000) - (start1.tv_sec * 1000 + start1.tv_usec / 1000));

    /* atlas version */
    struct timeval start2, stop2;
    gettimeofday(&start2, NULL);
    ATL_dsymv(121, n, alpha, vect_a, n, x, 1, beta, y, 1);
    gettimeofday(&stop2, NULL);
    time_spent_atlas = ((stop2.tv_sec * 1000 + stop2.tv_usec / 1000) - (start2.tv_sec * 1000 + start2.tv_usec / 1000));

    printf("Time for Simple dysmv is %lf ms\n", time_spent_simple);
    printf("Time for Atlas dysmv is %lf ms\n", time_spent_atlas);

    /* compare results */
    test(n, res, y);

    /* memory cleanup*/
    free(x);
    free(y);
    free(res);
    free(vect_a);
    for (i = 0; i < n; i++)
        free(a[i]);
    free(a);

    return 0;
}
