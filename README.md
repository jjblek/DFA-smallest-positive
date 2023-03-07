# CS 454 - Project 2

---
Given a positive integer k > 0, and a subset S of {0, 1, 2, · · · , 9} of digits, the goal is to find
the smallest positive integer N > 0 such that N%k = 0 and N uses only the digits from the
set S. 

    As an example, if k = 26147 and S = {1, 3}, the value of N = 1113313113. 

The obvious approach to this problem of generating the integers that use only the digits in S in succession
and testing if the integer is divisible by k is extremely inefficient and will take years to solve
on the test cases. By using a DFA, we can significantly speed up a solution to this problem.

## Description

---
### findString algorithm
Takes as input a DFA M and outputs a string w 
of shortest length (lexicographically first in case of more than one string) 
accepted by M. (If L(M) is empty, the algorithm outputs No solution.)
* Create a DFA M = <Q, Σ, δ, 0, F>
  * Q = {0, 1, · · · , k − 1}
  * F = {0}
  * δ(j, a) = (10 ∗ j + a) % k 
* call FindString with M and k as inputs

### delta function
From above, standalone delta function δ(j, a) = (10 ∗ j + a) % k

## Getting Started

---
### Executing program

* Execute program
```
cd <working directory>
make
./Project2
```
