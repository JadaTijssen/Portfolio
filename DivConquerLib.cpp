/* File:    DivConquerLib.cpp 
 * This file provides versions of the Divide and Conquer
 * algorithm for matrix multiplication.
 * Version: 28-06-2020
 * Author:  Jada R. Tijssen (jada.tijssen@gmail.com) 
 * Written as part of a Mathematics Bachelor thesis */

#include <iostream>
#include <float.h>

using namespace std;

#include "tropnum.h"
#include "DivConquerLib.hpp"
#include "standardLib.hpp"

#if 0
  #define Type double
  #define INITIALIZE 0
#else
  #define Type TropicalNumber
  #define INITIALIZE DBL_MAX
#endif

Type** matrixMult(Type **mat1, Type **mat2, Type **prod, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      prod[i][j] = INITIALIZE;
      for (int k = 0; k < n; k++)
      {
        prod[i][j] += mat1[i][k] * mat2[k][j];
      }
    }
  return prod;
}

Type** matrixMultiplicationSymmetric(Type **mat1, Type **mat2, Type **prod, int n) {
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
    {
      prod[i][j] = INITIALIZE;
      for (int k = 0; k < n; k++)
      {
        prod[i][j] += mat1[i][k] * mat2[k][j]; 
      }
      // Symmetric condition
      prod[j][i] = prod[i][j];
    }
  return prod;
}

void makeBlockMatrix(Type **block, Type **mat, int blockNumber, int sizeBlock) {
  // Case distinction on all blockmatrices
  switch (blockNumber)
  {
    case 11:
      for(int i = 0; i < sizeBlock; i++)
        for(int j = 0; j < sizeBlock; j++)
        {
          block[i][j] = mat[i][j];
        }
      break;
    
    case 12:
      for(int i = 0; i < sizeBlock; i++)
        for(int j = 0; j < sizeBlock; j++)
        {
          block[i][j] = mat[i][j + sizeBlock];
        }
      break;
      
    case 21:
      for(int i = 0; i < sizeBlock; i++)
        for(int j = 0; j < sizeBlock; j++)
        {
          block[i][j] = mat[i + sizeBlock][j];
        }
      break;
      
    case 22:
      for(int i = 0; i < sizeBlock; i++)
        for(int j = 0; j < sizeBlock; j++)
        {
          block[i][j] = mat[i + sizeBlock][j + sizeBlock];
        }
      break;
  }
}

void blocksToMatrix(Type **C, Type **C1, Type **C2, Type **C3, Type **C4, int n) {
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      if(i < n/2) { // i is between 0 and n/2
        if(j < n/2) {
          // j is between 0 and n/2
          C[i][j] = C1[i][j];
        } else {
          // j is between n/2 and n
          C[i][j] = C2[i][j-n/2];
        }
      } else { // i is between n/2 and n
        if(j < n/2) {
          // j is between 0 and n/2
          C[i][j] = C3[i-n/2][j];
        } else {
          // j is between n/2 and n
          C[i][j] = C4[i-n/2][j-n/2];
        }
      }
    }
}

int isPowerOf2(int n) {
  if (n > 0) {
    while (n%2 == 0)
      n /= 2;
    if (n == 1)
      return 1;
  }
  std::cout << "This is not a power of 2." << endl;
  return 0;
}

Type** divideConquer(Type **A, Type **B, Type **C, int n) {
  if (n <= 4){
    C = matrixMult(A, B, C, n);
    return C;
  }

  /* Allocate memory (nxn matrices and n/2 x n/2 matrices) */
  Type** P1 = make2DSquareArray(n);  
  Type** P2 = make2DSquareArray(n);  
  Type** C1 = make2DSquareArray(n);
  Type** C2 = make2DSquareArray(n);  
  Type** C3 = make2DSquareArray(n);
  Type** C4 = make2DSquareArray(n);
  Type** blockA = make2DSquareArray(n/2);
  Type** blockB = make2DSquareArray(n/2);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      P1[i][j] = INITIALIZE;
      P2[i][j] = INITIALIZE;
      C1[i][j] = INITIALIZE;
      C2[i][j] = INITIALIZE;
      C3[i][j] = INITIALIZE;
      C4[i][j] = INITIALIZE;
      if (i < n/2 && j < n/2)
      {
        blockA[i][j] = INITIALIZE;
        blockB[i][j] = INITIALIZE;
      }
    }

  //-----------------C1-----------------
  makeBlockMatrix(blockA, A, 11, n/2);         // Make block matrix A_11
  makeBlockMatrix(blockB, B, 11, n/2);         // Make block matrix B_11

  P1 = divideConquer(blockA, blockB, P1, n/2); // Multiply A_11 and B_11
  
  makeBlockMatrix(blockA, A, 12, n/2);         // Make block matrix A_12
  makeBlockMatrix(blockB, B, 21, n/2);         // Make block matrix B_21
  
  P2 = divideConquer(blockA, blockB, P2, n/2); // Multiply A_12 and B_21
  
  matrixAddition(P1, P2, C1, n/2);  // Compute C1 = A_11*B_11 + A_12*B_21
  
  //-----------------C2-----------------
  makeBlockMatrix(blockA, A, 11, n/2);
  makeBlockMatrix(blockB, B, 12, n/2);
  
  P1 = divideConquer(blockA, blockB, P1, n/2);
  
  makeBlockMatrix(blockA, A, 12, n/2);
  makeBlockMatrix(blockB, B, 22, n/2);
  
  P2 = divideConquer(blockA, blockB, P2, n/2);
  
  matrixAddition(P1, P2, C2, n/2);
  
  //-----------------C3-----------------
  makeBlockMatrix(blockA, A, 21, n/2);
  makeBlockMatrix(blockB, B, 11, n/2);
  
  P1 = divideConquer(blockA, blockB, P1, n/2);
  
  makeBlockMatrix(blockA, A, 22, n/2);
  makeBlockMatrix(blockB, B, 21, n/2);
  
  P2 = divideConquer(blockA, blockB, P2, n/2);
  
  matrixAddition(P1, P2, C3, n/2);
  
  //-----------------C4-----------------
  makeBlockMatrix(blockA, A, 21, n/2);
  makeBlockMatrix(blockB, B, 12, n/2);
  
  P1 = divideConquer(blockA, blockB, P1, n/2);
  
  makeBlockMatrix(blockA, A, 22, n/2);
  makeBlockMatrix(blockB, B, 22, n/2);
  
  P2 = divideConquer(blockA, blockB, P2, n/2);
  
  matrixAddition(P1, P2, C4, n/2);
  
  //------------------------------------
  
  blocksToMatrix(C, C1, C2, C3, C4, n);
 
  freeArr(P1, n);
  freeArr(P2, n);
  freeArr(C1, n);
  freeArr(C2, n);
  freeArr(C3, n);
  freeArr(C4, n);
  freeArr(blockA, n/2);
  freeArr(blockB, n/2);
  
  return C;
}

Type** divideConquerSymmetric(Type **A, Type **B, Type **C, int n, int depthRecursion) {
  if (n <= 64){
    if(depthRecursion == 0){
      C = matrixMultiplicationSymmetric(A, B, C, n);
    } else {
      C = matrixMult(A, B, C, n);
    }
    return C;
  }

  /* Allocate memory (nxn matrices and n/2 x n/2 matrices) */
  Type** P1 = make2DSquareArray(n);  
  Type** P2 = make2DSquareArray(n);  
  Type** C1 = make2DSquareArray(n);
  Type** C2 = make2DSquareArray(n);  
  Type** C3 = make2DSquareArray(n);
  Type** C4 = make2DSquareArray(n);
  Type** blockA = make2DSquareArray(n/2);
  Type** blockB = make2DSquareArray(n/2);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      P1[i][j] = INITIALIZE;
      P2[i][j] = INITIALIZE;
      C1[i][j] = INITIALIZE;
      C2[i][j] = INITIALIZE;
      C3[i][j] = INITIALIZE;
      C4[i][j] = INITIALIZE;
      if (i < n/2 && j < n/2)
      {
        blockA[i][j] = INITIALIZE;
        blockB[i][j] = INITIALIZE;
      }
    }
  
  //-----------------C1-----------------
  makeBlockMatrix(blockA, A, 11, n/2);         // Make block matrix A_11
  makeBlockMatrix(blockB, B, 11, n/2);         // Make block matrix B_11

  // Multiply A_11 and B_11
  P1 = divideConquerSymmetric(blockA, blockB, P1, n/2, depthRecursion + 1); 
  
  makeBlockMatrix(blockA, A, 12, n/2);         // Make block matrix A_12
  makeBlockMatrix(blockB, B, 21, n/2);         // Make block matrix B_21
  
  // Multiply A_12 and B_21
  P2 = divideConquerSymmetric(blockA, blockB, P2, n/2, depthRecursion + 1); 
  
  matrixAddition(P1, P2, C1, n/2);  // Compute C1 = A_11*B_11 + A_12*B_21
  
  //-----------------C2-----------------
  makeBlockMatrix(blockA, A, 11, n/2);
  makeBlockMatrix(blockB, B, 12, n/2);
  
  P1 = divideConquerSymmetric(blockA, blockB, P1, n/2, depthRecursion + 1);
  
  makeBlockMatrix(blockA, A, 12, n/2);
  makeBlockMatrix(blockB, B, 22, n/2);
  
  P2 = divideConquerSymmetric(blockA, blockB, P2, n/2, depthRecursion + 1);
  
  matrixAddition(P1, P2, C2, n/2);
  
  //-----------------C3-----------------
  if(depthRecursion == 0){
    C3 = computeTranspose(C2, C3, n/2);
  } else {
    makeBlockMatrix(blockA, A, 21, n/2);
    makeBlockMatrix(blockB, B, 11, n/2);
    
    P1 = divideConquerSymmetric(blockA, blockB, P1, n/2, depthRecursion + 1);
    
    makeBlockMatrix(blockA, A, 22, n/2);
    makeBlockMatrix(blockB, B, 21, n/2);
    
    P2 = divideConquerSymmetric(blockA, blockB, P2, n/2, depthRecursion + 1);
    
    matrixAddition(P1, P2, C3, n/2);
  }
  
  //-----------------C4-----------------
  makeBlockMatrix(blockA, A, 21, n/2);
  makeBlockMatrix(blockB, B, 12, n/2);
  
  P1 = divideConquerSymmetric(blockA, blockB, P1, n/2, depthRecursion + 1);
  
  makeBlockMatrix(blockA, A, 22, n/2);
  makeBlockMatrix(blockB, B, 22, n/2);
  
  P2 = divideConquerSymmetric(blockA, blockB, P2, n/2, depthRecursion + 1);
  
  matrixAddition(P1, P2, C4, n/2);
  
  //------------------------------------
  
  blocksToMatrix(C, C1, C2, C3, C4, n);
 
  freeArr(P1, n);
  freeArr(P2, n);
  freeArr(C1, n);
  freeArr(C2, n);
  freeArr(C3, n);
  freeArr(C4, n);
  freeArr(blockA, n/2);
  freeArr(blockB, n/2);
  return C;
}


