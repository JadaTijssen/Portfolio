/* File:    matPowerAndPath.cpp 
 * This is an implementation of an algorithm that solves
 * the APSP problem with tropical arithmetic.
 * Version: 28-06-2020
 * Author:  Jada R. Tijssen (jada.tijssen@gmail.com) 
 * Written as part of a Mathematics Bachelor thesis */

#include <iostream>
#include <float.h>

using namespace std;
#include "tropnum.h"
#include "LibQueue.hpp"
#include "DivConquerLib.hpp"
#include "timer.h"
#include "standardLib.hpp"

#if 0
  #define Type double
  #define INITIALIZE 0
#else
  #define Type TropicalNumber
  #define INITIALIZE DBL_MAX
#endif

Type** matrixMultiplication(Type **mat1, Type **mat2, Type **prod, int **next, int n) {
  int kTemp = -1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      prod[i][j] = INITIALIZE;
      for (int k = 0; k < n; k++) {
        prod[i][j] += mat1[i][k] * mat2[k][j];
        if(mat1[i][k] * mat2[k][j] == prod[i][j]) {
          // If the minimum value got updated, save for which k this happened.  
          kTemp = k;
        }
      }
      // This is to determine the next matrix, a.k.a. matrix X.
      if(prod[i][j] < mat1[i][j]) {
        /* If the new value found on(i,j) is STRICTLY smaller than
         * the one before multiplication, store this in next. */
        next[i][j] = next[i][kTemp];
      }
    }
  }
  return prod;
}

Type** matrixPower(int power, Type **N, Type **product, Type **tempProd, int **next, int n) {
  // Base case
  if(power == 1) {
    copy(product, N, n);
    return product;
  }

  product = matrixPower(power/2, N, product, tempProd, next, n);
  copy(tempProd, product, n);
  product = matrixMultiplication(tempProd, tempProd, product, next, n);
  //product = divideConquer(tempProd, tempProd, product, n);
  //product = matrixMultiplicationSymmetric(tempProd, tempProd, product, n);
  //product = divideConquerSymmetric(tempProduct, tempProduct, product, n, 0);

  if(power%2 == 1) { // The power is odd.
    copy(tempProd, product, n);
    product = matrixMultiplication(tempProd, N, product, next, n);
    //product = divideConquer(tempProd, N, product, n);
    //product = matrixMultiplicationSymmetric(tempProd, N, product, n);
    //product = divideConquerSymmetric(tempProduct, N, product, n, 0);
  }
  return product;
}

int** makeNextMatrix(int **next, Type **N, Type **APSP, int n) {
  Type min = INITIALIZE;
  int kTemp = -1;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(i != j){
        for(int k = 0; k < n; k++) {
          if(i != k && APSP[i][j] != DBL_MAX) {
            min += N[i][k]*APSP[k][j];
            if(min == N[i][k]*APSP[k][j]) { // If 'min' got updated...
              kTemp = k;
            }
          }
        }
        if(min < N[i][j] || kTemp == -1) { 
          /* If the new value found on(i,j) is STRICTLY smaller 
           * OR kTemp is not updated. */
          next[i][j] = kTemp;
        }
        kTemp = -1;
        min = INITIALIZE;
      } else {
        next[i][j] = -1; //i == j
      }
    }
  }
  return next;
}

Queue reconstructPath(Type **APSPmat, int **next, int start, int goal, int n) {
  Queue path = newQueue(n);
  
  if (APSPmat[start][goal] == DBL_MAX) return path; // There does not exist a path.
  
  int at = start;
  for (; at != goal; at = next[at][goal]) {
    enqueue(at, &path);
  }
  enqueue(goal, &path);
  return path;
}

void printPath(Queue path) {
  std::cout << "The shortest path is: " << endl;
  while(!isEmptyQueue(path)){
    std::cout << dequeue(&path);
    if(!isEmptyQueue(path)){
      std::cout << "-->";
    }
  }
  std::cout << endl;
}

void measureTime(Type** N, Type** product, int n) {
  Timer t;
  double minTime = DBL_MAX;
  
  for(int iter = 0; iter < 10; iter++)
  {
    t.startTimer();
    // This can be any function of which the running time needs to be measured.
    product = divideConquer(N, N, product, n);
    t.stopTimer();
    double sec = t.seconds();
    minTime = (sec < minTime ? sec : minTime);
  }
  std::cout << "Elapsed time: " << minTime << " seconds.\n";
}

int main(int argc, char *argv[]) {
  int n;
  std::cout << "Give the number of vertices:";
  std::cin >> n;
  
  /* Allocate memory (nxn matrices) */
  Type** N = make2DSquareArray(n);
  Type** product = make2DSquareArray(n);
  Type** tempProd = make2DSquareArray(n);
  int** next = make2DSquareArrayInt(n);
  int** next2 = make2DSquareArrayInt(n);
  
  /* Initialize square, tempProd, and product and scan N */
  std::cout << "Give the elements (from left to right):" << endl;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      product[i][j] = INITIALIZE;
      tempProd[i][j] = INITIALIZE;
      std::cin >> N[i][j];
      next[i][j] = j;
      next2[i][j] = j;
    }

  std::cout << "You entered:" << endl;
  printMatrix(N, n);
  
  int power = n-1;
  
  // This is only necessary when using divide and conquer:
  if(!isPowerOf2(n)) return 0;

  if(n > 2) {
    product = matrixPower(power, N, product, tempProd, next, n);
  }
  std::cout << "The (n-1)^th power is:" << endl;
  
  if(n > 2)
    printMatrix(product, n);
  else if (n == 1)
    std::cout << "1" << endl;
  else if (n == 2)
    printMatrix(N, n);
    
  // This is the next matrix constructed while running matrixMultiplication
  std::cout << "next:" << endl;
  printMatrixInt(next, n);
  
  // This is the next matrix that is constructed afterwards
  makeNextMatrix(next2, N, product, n);
  std::cout << "next2:" << endl;
  printMatrixInt(next2, n);
  
  // The following reconstructs the path
  std::cout << "Enter 'y' if you want to reconstruct a path. 'n' otherwise" << endl;
  char x;
  std::cin >> x;
  if(x == 'y') {
    int start, goal;
    std::cout << "Give the start vertex: " << endl;
    std::cin >> start;
    std::cout << "Give the goal vertex: " << endl;
    std::cin >> goal;
    Queue path;
    if(start == goal) {
      std::cout << "The start is aready the goal. " << endl;
    } else {
      path = reconstructPath(product, next2, start, goal, n);
      if (isEmptyQueue(path)) {
        std::cout << "There is no path between " << start << " and " << goal << endl;
      } else {
        printPath(path);
        std::cout << " of length " << product[start][goal] << endl;
      }
      freeQueue(path);
    }
  } else if (x == 'n') {}

  freeArr(N, n);
  freeArr(product, n);
  freeArr(tempProd, n);
  freeArrInt(next, n);
  freeArrInt(next2, n);
  return 0;
}
