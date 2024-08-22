#include <stdio.h>
#include <math.h>
#include "SSErrorCodes.h"
#include "SSStructures.h"
#include "SSOutput.h"
#include "SSSolve.h"

ExitCode FilePrintSolutions(FILE *fout_p, EquationRoots *roots_ptr)
{
    switch(roots_ptr->num_of_roots)
    {
        case NumOfRootsZERO:
        {
            fprintf(fout_p, "No solutions \n");
            break;
        }
        case NumOfRootsONE:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            fprintf(fout_p, "One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case NumOfRootsTWO:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            fprintf(fout_p, "First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case NumOfRootsINF_SOLS:
        {
            fprintf(fout_p, "Any number \n");
            break;
        }
        case NumOfRootsNAN:
        {
            return ExitCodeSOLVER_ERROR;
        }
    }
    return ExitCodeOK;
}

ExitCode PrintSolutions(EquationRoots *roots_ptr)
{
    switch(roots_ptr->num_of_roots)
    {
        case NumOfRootsZERO:
        {
            printf("No solutions \n");
            break;
        }
        case NumOfRootsONE:
        {
            if (!IsValid(roots_ptr->x1))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            printf("One solution: %lg \n", roots_ptr->x1);
            break;
        }
        case NumOfRootsTWO:
        {
            if (!IsValid(roots_ptr->x1) || !IsValid(roots_ptr->x2))
            {
                return ExitCodeOUTPUT_ERROR;
            }
            printf("First solution: %lg, second solution: %lg \n", roots_ptr->x1, roots_ptr->x2);
            break;
        }
        case NumOfRootsINF_SOLS:
        {
            printf("Any number \n");
            break;
        }
        case NumOfRootsNAN:
        {
            return ExitCodeSOLVER_ERROR;
        }
    }
    return ExitCodeOK;
}
