#include<stdio.h>

#define TAM 5000000

FILE *file;

double signal(double n) {
    
    if((int)n%2==0) {
        
        return 1.0;
    }
    return -1.0;
}

int main(int argc, char *argv[]) {
    
    static double pi = 0.0;
    
    file = fopen(argv[1], "w+");
    
    for(double n =0.0; n<TAM; n++) {
        
        pi += signal(n) /  (2*n+1);    
        
        fprintf(file, "%1.70f...\n", pi*4);
    }
    
    fclose(file);

    return 0;
}