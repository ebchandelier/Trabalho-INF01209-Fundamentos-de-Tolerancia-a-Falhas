#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {

  FILE *file = fopen(argv[1], "w+");

    fprintf(file, "%1.70f", 0.0);
    fclose(file);

  double A[4][4] = {-1, 0, 0, 1, 4, 10, -3, 2, 2, 0, 5, -3, 4, 1, 0, 6};//[-1 0 0 1,4 10 -3 2,2 0 5 -3;4 1 0 6];
  double b[4][1] = {{-2}, {5}, {11}, {7}};
  
  int N = 100;
  int n = sizeof(A[0]) / sizeof(A[0][0]);

file = fopen(argv[1], "w+");

for(int turn = 0; turn != 1000000; ++turn) {
	double x[4][1] = {-1, 1, -1, -1};
  int iter = 0;
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

  return 0;
}
