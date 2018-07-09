#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void gauss_seidel(double A[4][4], double b[4][1], double x[4][1], int N, int n, int iter) {
  N = 1000;
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

  // for(int k=0;k<4;k++) {
  //   fprintf(file, "%1.70f ", x[k][0]);
  //   fprintf(file, "\n");
  // }
}

bool isEqual(double A[100000][4], double B[100000][4]) {
  if (sizeof(A) != sizeof(B)) {
    return false;
  }
  for (int i=0; i<(sizeof(A)/sizeof(double)); i++) {
    if (A[i][0] != B[i][0]) {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[]) {
  //FILE *file;


  double A[4][4] = {-1, 0, 0, 1, 4, 10, -3, 2, 2, 0, 5, -3, 4, 1, 0, 6};
  double b[4][1] = {{-2}, {5}, {11}, {7}};
  double x_1[4][1] = {-1, 1, -1, -1};
  double x_2[4][1] = {-1, 1, -1, -1};
  double result_1[100000][4], result_2[100000][4];
  int N, n, iter;
  double A_temp[4][4], b_temp[4][1], x_temp[4][1];
  //file = fopen(argv[1], "w+");

  for (int l=0;l<100000;l++) {
    gauss_seidel(A, b, x_1, N, n, iter);
    gauss_seidel(A, b, x_2, N, n, iter);
    for(int g=0;g<4;g++){
      result_1[l][g] = x_1[g][1];
      result_2[l][g] = x_2[g][1];
    }
  }
  //fclose(file);


  FILE* file = fopen(argv[1], "w+");
  FILE* detectedFile = fopen("/tmp/gauss_seidel-detection.log", "w+");
  if (isEqual(result_1, result_2)) {
    for (int l=0;l<100000;l++) {
      for(int k=0;k<4;k++) {
        fprintf(file, "%1.70f ", result_1[l][k]);
        fprintf(file, "\n");
      }
    }
  }
  else {
    fprintf(file, "SDC");
  }
  fclose(detectedFile);
  fclose(file);

  return 0;
}
