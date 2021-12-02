#ifndef DIVCONQUERLIB_HPP
#define DIVCONQUERLIB_HPP

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

Type** matrixMultiplicationSymmetric(Type **mat1, Type **mat2, Type **prod, int n);
Type** matrixMult(Type **mat1, Type **mat2, Type **prod, int n);
void makeBlockMatrix(Type **block, Type **mat, int blockNumber, int sizeBlock);
void blocksToMatrix(Type **C, Type **C1, Type **C2, Type **C3, Type **C4, int n);
int isPowerOf2(int n);
Type** divideConquer(Type **A, Type **B, Type **C, int n);
Type** divideConquerSymmetric(Type **A, Type **B, Type **C, int n, int depthRecursion);

#endif
