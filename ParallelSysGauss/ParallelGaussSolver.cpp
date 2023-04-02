#include "GaussSolver.h"
#include <iostream>

using namespace std;

class ParallelGaussSolver : public GaussSolver
{
public:

    double* SolveSystem(double** mat, int N) override
    {
        /* reduction into r.e.f. */
        int singular_flag = forwardElim(mat, N);

        /* if matrix is singular */
        if (singular_flag != -1)
        {
            //printf("Singular Matrix.\n");

            /* if the RHS of equation corresponding to
               zero row  is 0, * system has infinitely
               many solutions, else inconsistent*/
            //if (mat[singular_flag][N])
            //    printf("Inconsistent System.");
            //else
            //    printf("May have infinitely many "
            //        "solutions.");
            return NULL;
        }

        /* get solution to system and print it using
           backward substitution */
        return backSub(mat, N);
    }
    ;
private:
    // function for elementary operation of swapping two rows
    void swap_row(double** mat, int N, int i, int j)
    {
        double* tmp = mat[i];
        mat[i] = mat[j];
        mat[j] = tmp;
    }

    // function to print matrix content at any stage
    void print(double** mat, int N)
    {
        for (int i = 0; i < N; i++, printf("\n"))
            for (int j = 0; j <= N; j++)
                printf("%lf ", mat[i][j]);

        printf("\n");
    }

    // function to reduce matrix to r.e.f.
    int forwardElim(double** mat, int N)
    {
        for (int k = 0; k < N; k++)
        {
            // Initialize maximum value and index for pivot
            int i_max = k;
            int v_max = mat[i_max][k];

            /* find greater amplitude for pivot if any */
            #pragma omp parallel for
            for (int i = k + 1; i < N; i++)
                if (abs(mat[i][k]) > v_max)
                    v_max = mat[i][k], i_max = i;

            /* if a principal diagonal element  is zero,
             * it denotes that matrix is singular, and
             * will lead to a division-by-zero later. */
            if (!mat[k][i_max])
                return k; // Matrix is singular

            /* Swap the greatest value row with current row */
            if (i_max != k)
                swap_row(mat, N, k, i_max);

            #pragma omp parallel for
            for (int i = k + 1; i < N; i++)
            {
                /* factor f to set current row kth element to 0,
                 * and subsequently remaining kth column to 0 */
                double f = mat[i][k] / mat[k][k];

                /* subtract fth multiple of corresponding kth
                   row element*/
                for (int j = k + 1; j <= N; j++)
                    mat[i][j] -= mat[k][j] * f;

                /* filling lower triangular matrix with zeros*/
                mat[i][k] = 0;
            }
        }
        return -1;
    }

    // function to calculate the values of the unknowns
    double* backSub(double** mat, int N)
    {
        double* x = new double[N];  // An array to store solution

        /* Start calculating from last equation up to the
           first */
        for (int i = N - 1; i >= 0; i--)
        {
            /* start with the RHS of the equation */
            x[i] = mat[i][N];

            /* Initialize j to i+1 since matrix is upper
               triangular*/
            #pragma omp parallel for
            for (int j = i + 1; j < N; j++)
            {
                /* subtract all the lhs values
                 * except the coefficient of the variable
                 * whose value is being calculated */
                x[i] -= mat[i][j] * x[j];
            }

            /* divide the RHS by the coefficient of the
               unknown being calculated */
            x[i] = x[i] / mat[i][i];
        }
        return x;
    }
};