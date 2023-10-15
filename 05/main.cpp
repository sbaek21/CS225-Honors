#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <climits>
#include <random>
#include <fstream>
#include <iomanip>

#define RANDTOP 10

inline int loc(int i, int j, int n)
{
    return ((n * i) + j);
}

// Print a n x n matrix
void printMatrix(double *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%f\t", a[loc(i, j, n)]);
        printf("\n");
    }
}

// Print a n long vector
void printVector(double *a, int n)
{
    printf("(");
    for (int i = 0; i < n; i++)
        printf("%f ", a[i]);
    printf(")\n");
}

// paralleled
void matmul(double *A, double *B, double *C, int n)
{
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
            {
                sum += A[loc(i, k, n)] * B[loc(k, j, n)];
            }
            C[loc(i, j, n)] = sum;
        }
    }
}

// not paralleled
void matmulSerial(double *A, double *B, double *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[loc(i, j, n)] = 0;
            for (int k = 0; k < n; k++)
            {
                C[loc(i, j, n)] += A[loc(i, k, n)] * B[loc(k, j, n)];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int n;
    double *A;
    double *B;
    double *C;

    std::cout << "Running with OMP max threads = " << omp_get_max_threads() << std::endl;

    printf("Size\tTime (Serial)\tTime (Parallel)\tSpeedup\n");
    for (n = 10; n <= 1000; n *= 10)
    {
        A = (double *)malloc(sizeof(double) * n * n);
        B = (double *)malloc(sizeof(double) * n * n);
        C = (double *)malloc(sizeof(double) * n * n);

        // Initialize matrices A and B
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[loc(i, j, n)] = i + j;
                B[loc(i, j, n)] = (i == j) ? 1 : 0;
                C[loc(i, j, n)] = 9;
            }
        }

        auto start_serial_matrix = std::chrono::high_resolution_clock::now();
        matmulSerial(A, B, C, n);
        auto end_serial_matrix = std::chrono::high_resolution_clock::now();
        auto duration_serial_matrix = std::chrono::duration_cast<std::chrono::microseconds>(end_serial_matrix - start_serial_matrix);

        auto start_parallel_matrix = std::chrono::high_resolution_clock::now();
        matmul(A, B, C, n);
        auto end_parallel_matrix = std::chrono::high_resolution_clock::now();
        auto duration_parallel_matrix = std::chrono::duration_cast<std::chrono::microseconds>(end_parallel_matrix - start_parallel_matrix);

        // Print the results in the desired format
        printf("%d\t%.6e\t%.6e\t%.2f\n", n, duration_serial_matrix.count() * 1e-6, duration_parallel_matrix.count() * 1e-6, duration_serial_matrix.count() / (double)duration_parallel_matrix.count());
    }

    return 0;
}
