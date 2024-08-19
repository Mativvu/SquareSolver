#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

struct equation { //ax^2+bx+c=0
    double a, b, c;
    double x1, x2;
};

void solve(struct equation *);
void print_solutions(struct equation *);
void input_koefs(struct equation *);
int isvalid(double koef);
int iszero(double koef);

int main()
{
    struct equation parabola = {NAN, NAN, NAN, NAN, NAN};
    struct equation *ptr = &parabola;

    input_koefs(ptr);

    solve(ptr);

    print_solutions(ptr);
}

void solve(struct equation *eqptr)
{
    double a, b, c;
    a = eqptr->a, b = eqptr->b, c = eqptr->c;

    if(!(isvalid(a) && isvalid(b) && isvalid(c)))
    {
        printf("Some of the koefs are wrong \n");
        return;
    }

    if(iszero(a)) // bx+c=0
    {
        if(iszero(b)) // c = 0
        {
            printf("c = 0 \n");
            return;
        }
        else // bx+c=0
        {
            printf("bx+c = 0 \n");
            eqptr->x1 = (iszero(c)) ? 0 : -(c/b);
        }
    }
    else // ax^2+bx+c=0
    {
        if(iszero(b) && c < -EPS) // ax^2+c=0
        {
            printf("ax^2+c = 0 \n");
            eqptr->x1 = sqrt(c/a);
            eqptr->x2 = -sqrt(c/a);
        }
        else // ax^2+bx+c=0
        {
            double D = b*b - 4*a*c;
            if(iszero(D)) // ax^2+bx=0
            {
                printf("ax^2+bx = 0 \n");
                eqptr->x1 = -b/(2*a);
            }
            else //ax^2+bx+c=0
            {
                printf("ax^2+bx+c = 0 \n");
                eqptr->x1 = (-b + sqrt(D))/(2*a);
                eqptr->x2 = (-b - sqrt(D))/(2*a);
            }
        }
    }
}

int iszero(double koef)
{
    return (fabs(koef) < EPS);
}

int isvalid(double koef)
{
    return (isfinite(koef) && !isnan(koef));
}

void input_koefs(struct equation *eqptr)
{
    printf("Введите коэффициенты уравнения ax^2+bx+c=0 в формате \"a b c\"\n");
    if(scanf("%lf %lf %lf", &eqptr->a, &eqptr->b, &eqptr->c) != 3)
    {
        printf("Wrong input");
        exit(0);
    };
    printf("Вы ввели: %lf % lf %lf \n", eqptr->a, eqptr->b, eqptr->c);
}

void print_solutions(struct equation *eqptr)
{
    if(eqptr->x1 == NAN)
    {
        printf("No solutions \n");
    }
    else if(eqptr->x2 == NAN)
    {
        printf("First solution == %lf \n", eqptr->x1);
    }
    else
        printf("First solution: %lf, second solution: %lf \n", eqptr->x1, eqptr->x2);
}
