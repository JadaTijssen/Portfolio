# Portfolio - Bachelor thesis

This is the collection of code used for my thesis project titled:
  "Solving the All Pairs Shortest Path Problem using Tropical Arithmetic".
  
Note that Tropical Arithmetic takes place on the semi-ring (R∪{∞},⊕,⊗,∞,0), where
the tropical operators ⊕ and ⊗ are defined by x ⊕ y:= min(x, y) and x ⊗ y:= x + y.

There is a theorem that states that in a weighted graph with n vertices that
contains no negative cycles, the n−1^th tropical power of the incidence matrix N
has at entry (i, j) the length of the shortest path from vertex v_i to vertex v_j.

In my thesis, I applied this theorem and used code to find the fastest way
to solve the APSP problem. This boils down to investigate how fast matrices
can be multiplied.

Therefore, different methods to multiply matrices are compared.

About the code:
The files tropnum.h and io.cpp create the **declaration?? object?? structure??** TropicalNumber so that for these variables the
tropical operator will be used correctly. 

timer.h is used to compute the running time of a chosen program. This is used to 
compare different matrix multiplication methods. 

In warshall.cpp, the Floyd Warshall method to solve the APSP problem is implemented.

standardLib.cpp and standardLib.h form a library with commonly used functions in
the project.

LibQueue.cpp and LibQueue.h form a library that creates a queue struct and contains
functions to create a queue and enqueue/dequeue/etc. your queue.

DivConquerLib.hpp and DivConquerLib.cpp contain functions that multiply matrices using
the divide and conquer method.

matPowerAndPath.cpp contains an implementation of an algorithm that solves the APSP problem
and reconstructs the paths. Here different approaches to matrix multiplication are used.
The time for each of those methods can be measured using timer.h
