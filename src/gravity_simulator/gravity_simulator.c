#include<stdio.h>
#include<math.h>
#include<time.h>
#include <unistd.h>
#include<iostream>

double G;

typedef struct obj {
    double pos_x;
    double pos_y;

    double vel_x;
    double vel_y;

    double mass;
} PLANET;

void printPlanet(PLANET planet) {
    printf("x: %.50f\n", planet.pos_x);
    printf("y: %.50f\n", planet.pos_y);
    printf("vx: %.50f\n", planet.vel_x);
    printf("vy: %.50f\n", planet.vel_y);
    printf("m: %.50f\n\n", planet.mass );

}

double distance_between (PLANET a, PLANET b) {
    
    double x1 = a.pos_x;
    double x2 = b.pos_x;
    double y1 = a.pos_y;
    double y2 = b.pos_y;

    return sqrt(pow(x2-x1, 2.0) + pow(y2-y1, 2.0));
}

double distance_x(PLANET a, PLANET b) {

    return b.pos_x - a.pos_x;
}

double distance_y(PLANET a, PLANET b) {

    return b.pos_y - a.pos_y;
}

double my_sin(PLANET a, PLANET b) {

    return  distance_y(a,b) / distance_between(a,b);
}

double my_cos(PLANET a, PLANET b) {

    return distance_x(a,b) / distance_between(a,b);
}

void move(PLANET *a, PLANET b) {
    double distanceBetween = distance_between(*a,b);
    
    if(distanceBetween > 1 || distanceBetween < -1) {

        double gravity_force = G * a->mass * b.mass / pow(distanceBetween, 2.0);
        

        a->vel_x += gravity_force/a->mass*my_cos(*a,b);
        a->vel_y += gravity_force/a->mass*my_sin(*a,b);
        // printf("velo delta: %.50f\n", gravity_force);

    }
    a->pos_x += a->vel_x;
    a->pos_y += a->vel_y;
}

int main(int argc, char *argv[]) {
    
    G = 6.674 * pow(10.0,-11.0);

    PLANET a;
    a.pos_x = 0.0;
    a.pos_y = 0.0;
    a.vel_x = 0.0;
    a.vel_y = 0.0;
    a.mass = 1000000000;


    PLANET b;
    b.pos_x = -10.0;
    b.pos_y = -10.0;
    b.vel_x = 1.0;
    b.vel_y = 0.0;
    b.mass = 1;

    for(int i = 0 ; i < 80000000; i++) {
        move(&b, a);
        // printPlanet(a);
        // usleep(10000);
    }

    std::cout << argv[1] << " <=\n";

    FILE* file = fopen(argv[1], "w+");
    fprintf(file, "x: %.50f", b.pos_x);
    fprintf(file, "y: %.50f\n", b.pos_y);
    fprintf(file, "vx: %.50f\n", b.vel_x);
    fprintf(file, "vy: %.50f\n", b.vel_y);

    fclose(file);

        printPlanet(b);

    return 0;
}