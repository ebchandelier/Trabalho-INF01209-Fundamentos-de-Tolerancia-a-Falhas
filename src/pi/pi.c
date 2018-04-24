#include<stdio.h>

#define TAM 100000


double signal(double n) {
    
    if((int)n%2==0) {
        
        return 1.0;
    }
    return -1.0;
}

int main(int argc, char *argv[]) {
    
    FILE *file = fopen(argv[1], "w+");
    
    fprintf(file, "%1.70f", 0.0);
    fclose(file);

    for(double n =0.0; n<TAM; n++) {
        
        double readPi;

        file = fopen(argv[1], "w+");

        fscanf(file, "%1.70f", &readPi);

        readPi += signal(n) /  (2*n+1);    
        
        // readPi * 4 = 3.1415....
        fprintf(file, "%1.70f", readPi);


        fclose(file);
    }

    return 0;
}