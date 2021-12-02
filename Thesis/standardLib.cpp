/* File:    standardLib.cpp 
 * This file provides frequently used functions in the code
 * that solves the APSP problem with tropical arithmetic.
 * Version: 28-06-2020
 * Author:  Jada R. Tijssen (jada.tijssen@gmail.com) 
 * Written as part of a Mathematics Bachelor thesis */

#include <iostream>
#include <float.h>
using namespace std;

#include "tropnum.h"
#include "standardLib.hpp"

#if 0
  #define Type double
  #define INITIALIZE 0
#else
  #define Type TropicalNumber
  #define INITIALIZE DBL_MAX
#endif

Type **make2DSquareArray(int n) {
  Type** arr = new Type*[n];
  for(int i = 0; i < n; ++i)
  {
    arr[i] = new Type[n];
  }
  return arr;
}

int **make2DSquareArrayInt(int n) {
  int** arr = new int*[n];
  for(int i = 0; i < n; ++i)
  {
    arr[i] = new int[n];
  }
  return arr;
}

void copy(Type **mat1, Type **mat2, int n) {
   for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mat1[i][j] = mat2[i][j];
}

void freeArr(Type **arr, int n) {
  for(int i = 0; i < n; i++)
  {
    delete [] arr[i];
  }
  delete [] arr;
}

void freeArrInt(int **arr, int n) {
  for(int i = 0; i < n; i++)
  {
    delete [] arr[i];
  }
  delete [] arr;
}

void printMatrix(Type **arr, int n) {
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      std::cout << arr[i][j] << "      ";
    }
    std::cout << endl;
  }
}

void printMatrixInt(int **arr, int n) {
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      std::cout << arr[i][j] << "      ";
    }
    std::cout << endl;
  }
}

int compare(Type **mat1, Type **mat2, int n) {
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      if(mat1[i][j] != mat2[i][j])
        return 0;
    }
  return 1;
}

Type** computeTranspose(Type **A, Type **transpose, int n) {
  Type dummy;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
      transpose[i][j] = A[j][i];
    }
  return transpose;
}

void matrixAddition(Type **A, Type **B, Type **C, int n) {
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      C[i][j] = A[i][j] + B[i][j];
    }
}
