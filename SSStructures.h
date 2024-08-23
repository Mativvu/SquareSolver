#ifndef SSSTRUCTURES_H
#define SSSTRUCTURES_H

const int INF_SOLS = 3;
const int NAN_ROOTS = -1;

struct EquationCoeffs {
    double a, b, c;
};

struct EquationRoots {
    int num_of_roots;
    double x1, x2;
};

#endif
