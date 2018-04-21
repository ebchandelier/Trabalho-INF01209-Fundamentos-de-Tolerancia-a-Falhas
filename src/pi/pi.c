#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    double pi = 0.0;
    for(double n =0.0; n<10000000.0; n++) {
        pi += pow(-1.0, n) /  (2*n+1);    
    }
    
    FILE *file = fopen(argv[1], "w");
    FILE *fileAux = fopen("aiaiai", "a+");


    char output[55];
    snprintf(output, 55, "%1.50f", pi*4);
    
    fputs(output, fileAux);
    fputs(output, file);

    fclose(fileAux);
    fclose(file);
    printf("SAVED =====> %1.50f <=====\n", pi*4);
    // printf("SAVED ===> %s on ===> %s\n", output, argv[1]);
    return 0;
}

// # pi = 0
// # for n in range(100000):
// #     pi += (-1)**n /  (2*n+1)
// # print(pi*4)