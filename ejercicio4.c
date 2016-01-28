#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

#define MAXN 5000  /* Max value of N */
int N; //size matrix

volatile float A[MAXN][MAXN], B[MAXN], X[MAXN];

void gauss(); 


void parameters(int argc, char **argv) {
  N = atoi(argv[1]);
  printf("\nMatrix dimension N = %i.\n", N);
}


void initialize_inputs() {
  int row, col;

  printf("\nInitializing...\n");
  for (col = 0; col < N; col++) {
    for (row = 0; row < N; row++) {
      A[row][col] = (float)rand() / 32768.0;
    }
    B[col] = (float)rand() / 32768.0;
    X[col] = 0.0;
  }

}

void print_inputs() {
  int row, col;

    printf("\nA =\n\t");
    for (row = 0; row < N; row++) {
      for (col = 0; col < N; col++) {
    printf("%5.2f%s", A[row][col], (col < N-1) ? ", " : ";\n\t");
      }
    }
    printf("\nB = [");
    for (col = 0; col < N; col++) {
      printf("%5.2f%s", B[col], (col < N-1) ? "; " : "]\n");
    }
  
}

void print_X() {
  int row;
    printf("\nX = [");
    for (row = 0; row < N; row++) {
      printf("%5.2f%s", X[row], (row < N-1) ? "; " : "]\n");
    }
  
}

int main(int argc, char **argv) {

  parameters(argc, argv);
  initialize_inputs();
  print_inputs();

  gauss();

  print_X();
  
  exit(0);
}

void gauss() {
  int norm, row, col; 
  float multiplier;

  for (norm = 0; norm < N - 1; norm++) {

    #pragma omp parallel num_threads(2) firstprivate(norm)
    #pragma omp parallel for
    for (row = norm + 1; row < N; row++) {
      multiplier = A[row][norm] / A[norm][norm];      
      for (col = norm; col < N; col++) {
          A[row][col] -= A[norm][col] * multiplier;
      }
      B[row] -= B[norm] * multiplier;
    }
  }

  for (row = N - 1; row >= 0; row--) {
    X[row] = B[row];
    for (col = N-1; col > row; col--) {
      X[row] -= A[row][col] * X[col];
    }
    X[row] /= A[row][row];
  }
}