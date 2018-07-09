#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void gauss_seidel(FILE *file, double A[4][4], double b[4][1], double x[4][1], int N, int n, int iter) {
  N = 100;
  n = sizeof(A[0]) / sizeof(A[0][0]);
  iter = 0;
    while (iter < N) {
      iter += 1;
      for(int i=0;i<n;i++) {
        x[i][0] = b[i][0];
        for(int j=0;j<n;j++) {
          if(i != j) {
            x[i][0] -= (A[i][j]) * (x[j][0]);
          }
        }
        x[i][0] /= (A[i][i]);
      }
    }

  for(int k=0;k<4;k++) {
    fprintf(file, "%1.70f ", x[k][0]);
    fprintf(file, "\n");
  }
}

int main(int argc, char *argv[]) {

  FILE *file;

  double A[4][4] = {-1, 0, 0, 1, 4, 10, -3, 2, 2, 0, 5, -3, 4, 1, 0, 6};
  double b[4][1] = {{-2}, {5}, {11}, {7}};
  double x[4][1] = {-1, 1, -1, -1};
  int N, n, iter;
  double A_temp[4][4], b_temp[4][1], x_temp[4][1];
  file = fopen(argv[1], "w+");

  for (int l=0;l<500000;l++) {
    gauss_seidel(file, A, b, x, N, n, iter);
  }
  fclose(file);

  return 0;
}
