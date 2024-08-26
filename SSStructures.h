/*!
* \file
* \brief Structs EquationCoeffs for coefficients and
* EquationRoots to store solutions and num of roots.
* Enum ::NumOfRoots to limit using impossible values for
* num of roots, also INF_SOLS for infinite solutions
* and NAN for initialization.
*/

/** \enum NumOfRoots
* \brief Enum to store values for num_of_roots from EquationRoots.
*
* \details Enum is used to limit using impossible values for
* num of roots, also INF_SOLS for infinite solutions
* and NAN for initialization.
*/

/** \struct EquationCoeffs
* \brief Struct for storing coefficients.
*
* \details Stores 3 coefficients: a, b and c.
*/

/** \struct EquationRoots
* \brief Struct for storing solutions and number of them.
*
* \details
*  - Stores variables:
*       - Number of solutions num_of_roots
*       - First solution x1
*       - Second solution x2
*/

#ifndef SSSTRUCTURES_H
#define SSSTRUCTURES_H

enum NumOfRoots {
    NumOfRootsZERO     = 0,  /**< Zero solutions */
    NumOfRootsONE      = 1,  /**< One solution */
    NumOfRootsTWO      = 2,  /**< Two solution */
    NumOfRootsINF_SOLS = -1, /**< Infinite solution */
    NumOfRootsNAN      = -2  /**< Initialization value */
};

struct EquationCoeffs {
    double a, b, c;
};

struct EquationRoots {
    NumOfRoots num_of_roots;
    double x1, x2;
};

#endif
