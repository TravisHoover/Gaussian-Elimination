/*
 * Author: Travis Hoover
 * Course: CSCI 4330
 * Professor: Dr. Pettey
 * Date: 2/15/2017
 *
 * This program will use a modified version of Gaussian Elimination to determine the
 * inverse of matrices. The program will also use pthreads for concurrent computing
 * */


//USE 2 CONDITION VARIABLES AND ONE MUTEX

#include <stdio.h>


int main()
{
    int size, j;
    float A[10][10];
    float B[10][10];
    float div, mult;

    // Prompt for matrix size
    printf( "\nInput the number of items: ");
    scanf("%d", &size);

    // Input matrix A
    printf ("\nInput matrix A: \n");
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            scanf("%f", &A[i][j]);

    // Input Matrix B
    printf ("\nInput matrix B: \n");
    for(int i = 0; i < size; i++)
        scanf("%f", &B[i][j]);

    // Populate inverse
    for(int i = 0; i < size; i++) {

        // Select Pivot
        div = A[i][i];

        for(int j = 0; j < size; j++) {
            A[i][j] /= div;
        }
        B[i][j] /= div;

        for(int k = 0; k < size; k++) {
            if(k != i) {

                mult = A[k][i];
                for(int j = 0; j < size; j++) {
                    A[k][j] -= (mult * A[i][j]);
                }
                *B[k] -= (mult * (*B[i]));
            }
        }
    }

    printf( "\nThe X values are: \n");
    for(int i = 0; i < size; i++) {
            printf("%.6f \n", B[i][j]);
    }

    return 0;
}