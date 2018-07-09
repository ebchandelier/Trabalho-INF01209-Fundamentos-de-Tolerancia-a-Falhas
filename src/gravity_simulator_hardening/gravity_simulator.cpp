#include<stdio.h>
#include<cmath>
// #include<time.h>
// #include<unistd.h>
#include<iostream>

double G;

typedef struct obj {
    double pos_x;
    double pos_y;

    double vel_x;
    double vel_y;

    double mass;
} PLANET;

bool checkForSDC(double original, double copy) {

    if(original != copy) 
    { 
        FILE* detectedFile = fopen("/tmp/gravity_simulator-detection.log", "w+");
        fprintf(detectedFile, "nada...");
        fclose(detectedFile);

        return true;
    } 

    return false;
}

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

    return distance_y(a,b) / distance_between(a,b);
}

double my_cos(PLANET a, PLANET b) {

    return distance_x(a,b) / distance_between(a,b);
}

void move(PLANET *a, PLANET b) {

    double distanceBetween = distance_between(*a,b);
    
    if(distanceBetween > 2.0 || distanceBetween < -2.0) {

        double gravity_force_original = G * a->mass * b.mass / pow(distanceBetween, 2.0);
        double gravity_force_copy = G * a->mass * b.mass / pow(distanceBetween, 2.0);
        if(checkForSDC(gravity_force_original, gravity_force_copy)) return;

        double cos_original = gravity_force_original*my_cos(*a,b)/a->mass;
        double cos_copy = gravity_force_original*my_cos(*a,b)/a->mass;
        if(checkForSDC(cos_original, cos_copy)) return;
        a->vel_x += cos_original;

        double sin_original = gravity_force_original*my_sin(*a,b)/a->mass;
        double sin_copy = gravity_force_original*my_sin(*a,b)/a->mass;
        if(checkForSDC(sin_original, sin_copy)) return;
        a->vel_y += sin_original;
    }

    a->pos_x += a->vel_x;
    a->pos_y += a->vel_y;
}

void write(FILE* file, PLANET b) {

    fprintf(file, "x: %.50f", b.pos_x);
    fprintf(file, "y: %.50f\n", b.pos_y);
    fprintf(file, "vx: %.50f\n", b.vel_x);
    fprintf(file, "vy: %.50f\n", b.vel_y);
}

int main(int argc, char *argv[]) {
    
    G = 6.674 * pow(10.0,-11.0);

    PLANET a;
    a.pos_x = 0.0;
    a.pos_y = 0.0;
    a.vel_x = 0.0;
    a.vel_y = 0.0;
    a.mass = 1000000;

    PLANET b;
    b.pos_x = -10.0;
    b.pos_y = -10.0;
    b.vel_x = 0.0;
    b.vel_y = 0.0;
    b.mass = 1000;

    PLANET c;
    c.pos_x = -10.0;
    c.pos_y = 10.0;
    c.vel_x = 0.0;
    c.vel_y = 0.0;
    c.mass = 2000;

    PLANET d;
    d.pos_x = -10.0;
    d.pos_y = 10.0;
    d.vel_x = 0.0;
    d.vel_y = 0.0;
    d.mass = 3000;

    PLANET e;
    e.pos_x = -5.0;
    e.pos_y = 5.0;
    e.vel_x = 0.0;
    e.vel_y = 0.0;
    e.mass = 4000;

    PLANET f;
    f.pos_x = 10.0;
    f.pos_y = 5.0;
    f.vel_x = 0.0;
    f.vel_y = 0.0;
    f.mass = 100;

    FILE* file = fopen(argv[1], "w+");
    for(int i = 0 ; i < 2500000; i++) {
        move(&a, b);
        move(&a, c);
        move(&a, d);
        move(&a, e);
        move(&a, f);
        
        move(&b, a);
        move(&b, c);
        move(&b, d);
        move(&b, e);
        move(&b, f);
        
        move(&c, a);
        move(&c, b);
        move(&c, d);
        move(&c, e);
        move(&c, f);
        
        move(&d, a);
        move(&d, b);
        move(&d, c);
        move(&d, e);
        move(&d, f);
        
        move(&e, a);
        move(&e, b);
        move(&e, c);
        move(&e, d);
        move(&e, f);
        
        
        move(&f, a);
        move(&f, b);
        move(&f, c);
        move(&f, d);
        move(&f, e);

    }

    write(file, a);
    write(file, b);
    write(file, c);
    write(file, d);
    write(file, e);
    write(file, f);



    fclose(file);

    return 0;
}