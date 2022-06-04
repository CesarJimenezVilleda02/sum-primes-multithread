/*************************************************************
* File: main.cpp
* Author: Pablo César Jiménez Villeda y Ariann Fernando Arriaga Alcántara
* Description: Este archivo contiene una funcion usada para determinar si un numero
*              es primo o no.
* Date: 06/06/2022
*************************************************************/

#ifndef ISPRIME_H
#define ISPRIME_H

#include <cmath>
#include <iostream>

using namespace std;

// =================================================================
// isPrime. Check if a number is prime.
//
// @param n	The number to evaluate.
// @return	A boolean that is true when the number is prime.
/*ANÁLISIS DE ALGORITMO:
Dado que se itera n^1/2 veces donde n es el numero en cuestion,
ya que se revisan los numeros previos a la raiz de la entrada la
complejidad aumentara de forma lineal, por lo que la complejidad
es de O(n).
*/
// =================================================================
bool isPrime(int n) {
    // Corner case
    if (n <= 1)
        return false;

    double limit = sqrt(n);

    // Check from 2 to n-1
    for (int i = 2; i <= limit; i++){
        if (n % i == 0) {
          return false;
        }
    }

    return true;
}

#endif /* ISPRIME_H */
