/*************************************************************
* File: main.cpp
* Author: Pablo César Jiménez Villeda y Ariann Fernando Arriaga Alcántara
* Description: Este archivo contiene una demostracion del uso de programacion
*              multihilo y monohilo para encontrar la sumatoria de numeros primos
*              del 0 al 5,000,000.
* Date: 06/06/2022
*************************************************************/

#include "isPrime.h"
#include "utils.h"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex_lock;
const int THREADS = 8;
const int LIMIT = 5000000;

/*--------------------- MONO HILO ---------------------*/
// =================================================================
// sumPrime. Sum all prime numbers up to a limit.
//
// @param limit	The limit whose previous prime numberss will be added.
// @return	The sum of all prime numbers.
/*ANÁLISIS DE ALGORITMO:
Si se tiene un limite n, por cada numero se realizara la operacion
isPrime, la cual tiene una complejidad de O(n), por lo que la
complejidad total es de O(n^2).
*/
// =================================================================
double sumPrime(int limit) {
  double acum = 0;

  for (int i = 0; i <= limit; i++) {
    if(isPrime(i)) acum += i;
  }

  return acum;
}

// /*--------------------- MULTI HILO ---------------------*/
typedef struct {
  double start, end; // [start, end)
} Block;

// =================================================================
// partialSumPrime. Sum all prime numbers betweem an upper and a lower limit.
//
// @param param	A Block in which both limits are defined.
// @return	The sum of all prime numbers within the range.
/*ANÁLISIS DE ALGORITMO:
Si se tiene una cantidad de numeros n entre los limites, por cada numero se
realizara la operacion isPrime, la cual tiene una complejidad de O(n),
por lo que la complejidad total es de O(n^2).
*/
// =================================================================
void* partialSumPrime(void* param) {
  double *acum;
  Block *block;

  block = (Block *) param;
  acum =  new double;
  (*acum) = 0;
  for (int i = block->start; i < block->end; i++) {
    if(isPrime(i)) (*acum) += i;
  }

  return acum;
}

int main() {
  // --- MONOHILO
  start_timer();

  double resultMono = sumPrime(LIMIT);
  double timeMono = stop_timer();
  cout << "The result is: " << fixed << setprecision(0) << resultMono << endl;
  cout << "This operation took: " << fixed << setprecision(2) << timeMono << " ms using one thread" << endl;

  // --- MULTIHILO
  int *a, blockSize, i, j;
	double ms, result, *acum;
  Block blocks[THREADS];
  pthread_t tids[THREADS];

  blockSize = (LIMIT + 1) / THREADS;
  for (i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : LIMIT + 1;
  }
  
  start_timer();
  result = 0;
  for (i = 0; i < THREADS; i++) {
    pthread_create(&tids[i], NULL, partialSumPrime, (void*) &blocks[i]);
  }

  for (i = 0; i < THREADS; i++) {
      pthread_join(tids[i], (void**) &acum);
      result += (*acum);
      delete acum;
  }

  double timeMulti = stop_timer();
  cout << "The result is: " << fixed << setprecision(0) << result << endl;
  cout << "This operation took: " << fixed << setprecision(2) << timeMulti << "ms using " << THREADS << " threads" << endl;

  cout << "The speedup using " << THREADS << " prcessors is " << fixed << setprecision(4) << timeMono / timeMulti << endl;

  return 0;
}
