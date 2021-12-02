#ifndef STANDARDLIB_HPP
#define STANDARDLIB_HPP

#include <iostream>
#include <float.h>
#include "tropnum.h"

#if 0
  #define Type double
  #define INITIALIZE 0
#else
  #define Type TropicalNumber
  #define INITIALIZE DBL_MAX
#endif

Type **make2DSquareArray(int n);
int **make2DSquareArrayInt(int n);
void copy(Type **mat1, Type **mat2, int n);
void freeArr(Type **arr, int n);
void freeArrInt(int **arr, int n);
void printMatrix(Type **arr, int n);
void printMatrixInt(int **arr, int n);
int compare(Type **mat1, Type **mat2, int n);
Type **computeTranspose(Type **A, Type **transpose, int n);
void matrixAddition(Type **A, Type **B, Type **C, int n);

#endif
