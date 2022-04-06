#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv) {
   
    long **a, **b, **c;
    int N = 4;

    if (argc == 2) {
      N = atoi (argv[1]);
      assert (N > 0);
    }

    int i,j,k,mul=2;
    int col_sum = N * (N-1) / 2;

    a = (long **)malloc (N * sizeof(long *));
    b = (long **)malloc (N * sizeof(long *));
    c = (long **)malloc (N * sizeof(long *));
    for (i=0; i<N; i++) {
      a[i] = (long *)malloc (N * sizeof(long));
      b[i] = (long *)malloc (N * sizeof(long));
      c[i] = (long *)malloc (N * sizeof(long));
    }


    for (i=0; i<N; i++)
      for (j=0; j<N; j++) {
	a[i][j] = i*mul;
	b[i][j] = i;
	c[i][j] = 0;
      }

    printf ("Matrix generation finished.\n");

    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
            printf("%ld ", c[i][j]);
        printf("\n");

    printf ("Test finished.\n");

    int n, chunk, tid;
    float result;
    chunk  = 10;
    result = 0.0;

    #pragma omp parallel for       \
        default(shared) private(i) \
            schedule(static, chunk) \
            reduction(+:result)

        for(i = 0; i < N; i++){
            //#pragma omp for
            #pragma omp parallel private(tid)
            for (i=0; i<N; i++)   
      	        for (j=0; j<N; j++)
			for (k=0; k<N; k++)
	  			c[i][j] += a[i][k] * b[k][j];

        printf ("Multiplication finished.\n");   
        };

        //printf("Final result = %f\n",result);

    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
            printf("%ld ", c[i][j]);
        printf("\n");

    printf ("Test finished.\n");

    //return 0;
}
