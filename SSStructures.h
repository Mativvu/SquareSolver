#ifndef SSSTRUCTURES_H
#define SSSTRUCTURES_H

enum NumOfRoots {
    NumOfRootsZERO,
    NumOfRootsONE,
    NumOfRootsTWO,
    NumOfRootsINF_SOLS,
    NumOfRootsNAN
};

struct EquationCoeffs {
    double a, b, c;
};

struct EquationRoots {
    int num_of_roots;
    double x1, x2;
};

#endif
