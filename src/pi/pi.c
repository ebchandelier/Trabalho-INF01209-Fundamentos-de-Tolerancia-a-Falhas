#include<stdio.h>
#include<math.h>

int main() {
    double pi = 0.0;
    for(double n =0.0; n<10000.0; n++) {
        pi += pow(-1.0, n) /  (2*n+1);    
    }
    printf("%f\n", pi*4);
    return 0;
}

// # pi = 0
// # for n in range(100000):
// #     pi += (-1)**n /  (2*n+1)
// # print(pi*4)