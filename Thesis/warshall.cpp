/* File:    warshall.cpp 
 * This is an implementation of the Floyd Warshall Algorithm
 * (solving the All Pairs Shortest Path problem)
 * Version: 28-06-2020
 * Author:  Jada R. Tijssen (jada.tijssen@gmail.com) 
 * Written as part of a Mathematics Bachelor thesis */

#include <iostream>

using namespace std;

void floydWarshall(double **N, int n, int **next) {
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (N[i][j] > N[i][k] + N[k][j]) {
          N[i][j] = N[i][k] + N[k][j];
          next[i][j] = next[i][k];
        }

  // Negative cycles:
  int negCycle = 0;
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (N[i][j] > N[i][k] + N[k][j]) {
          negCycle = 1;
        }
  if(negCycle == 1){
    std::cout << "Negative cycle!" << endl;
  }
}

void printMatrix(double **arr, int n) {
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

void freeArr(double **arr, int n) {
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

int main(int argc, char *argv[]) {
  int n;
  std::cout << "Give the number of vertices:";
  std::cin >> n;

  /* Allocate memory (nxn matrix) */
  double** N = new double*[n];
  int** next = new int*[n];
  for(int i = 0; i < n; ++i)
  {
    N[i] = new double[n];
    next[i] = new int[n];
  }

  /* Scan N */
  std::cout << "Give the elements (from left to right):" << endl;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      std::cin >> N[i][j];
      next[i][j] = j;
    }

  std::cout << "You entered:" << endl;
  printMatrix(N, n);
  
  floydWarshall(N, n, next);
  
  std::cout << "The Floyd-Warshall algorithm computed:" << endl;
  printMatrix(N, n);
  
  std::cout << "next:" << endl;
  printMatrixInt(next, n);
    
  freeArr(N, n);
  freeArrInt(next, n);
  return 0;
}
