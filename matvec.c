#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <immintrin.h>

void init_vec(double *x, int N);
void zero_vec(double *x, int N);
void init_mat(double *a, int N, int M);
int check(double *b, int N, int M);

// Computes b = Ax
// A in a N-by-M matrix
// x is a N element vector
// b is n M element vector
void dgemv(int N, int M, double const *restrict A, double const * restrict x, double *restrict b) {
  A = __builtin_assume_aligned(A, 64);
  x = __builtin_assume_aligned(x, 64);
  b = __builtin_assume_aligned(b, 64);
  // #pragma assume holds(N%8==0)
  #pragma simd aligned(A, x, b: 64)
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      b[j] += A[j + M*i] * x[i];
    }
  }
}

int main(int argc, char *argv[]) {

  int N = 10001;
  int M = 10000;

  // If command line argument, then set the length of the array
  if (argc == 2) {
    N = atoi(argv[1]);
    M = atoi(argv[1]);
  }
  if (argc == 3) {
    N = atoi(argv[1]);
    M = atoi(argv[2]);
  }
  printf("running dgemv with a %d-by-%d matrix\n", N, M);

  double * x = aligned_alloc(64, sizeof(double) * N);
  double * b = aligned_alloc(64, sizeof(double) * M);
  double * a = aligned_alloc(64, sizeof(double) * N * M);

  // Initalise
  init_vec(x, N);
  zero_vec(b, N);
  init_mat(a, N, M);

  double tic = omp_get_wtime();
  dgemv(N, M, a, x, b);
  double toc = omp_get_wtime();

  int correct = check(b, N, M);
  if (!correct) printf("ERROR: RESULT INCORRECT\n");
  else printf("CORRECT\n");

  printf("dgemv took %lfs\n", toc-tic);

  free(x);
  free(b);
  free(a);

  return EXIT_SUCCESS;
}

void init_vec(double *x, int N) {
  for (int i = 0; i < N; ++i) {
    x[i] = (double)i + 1.0;
  }
}

void zero_vec(double *x, int N) {
  for (int i = 0; i < N; ++i) {
    x[i] = 0.0;
  }
}

void init_mat(double *A, int N, int M) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      A[j + M*i] = 1.0;
    }
  }
}

int check(double *y, int N, int M) {
  double r = (double) N * (double)(N+1) / 2.0;
  for (int i = 0; i < M; ++i) {
    if (fabs(y[i] - r) > 1.0E-12) {
	    printf("y[%d] = %lf != %lf\n", i, y[i], r);
      return 0;
    }
  }
  return 1;
}

